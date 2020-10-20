using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Linq;

namespace IMMRequest.BusinessLogic
{
    public class RequestLogic : IRequestLogic
    {
        private readonly IUnitOfWork unitOfWork;

        public RequestLogic(IUnitOfWork unitOfWork)
        {
            this.unitOfWork = unitOfWork;
        }

        public int Add(RequestEntity request)
        {
            ValidateRequestIdExistance(request.Id);
            ValidateTypeForRequestExistance(request.RequestTypeEntityId);
            request.Status = "CREADA";
            request.StatusDetail = "La solicitud fue creada";
            request.AdditionalFieldsValues = createAdditionalFieldsValues(request);
            request.Date = DateTime.Now;

            getFathersNames(request);

            if (unitOfWork.UserRepository.Exists(u => u.Mail == request.Mail && !u.IsDeleted))
            {
                UserEntity user = unitOfWork.UserRepository.FirstOrDefault(u => u.Mail == request.Mail);
                request.ApplicantName = user.CompleteName;
                if (user.Requests == null)
                    user.Requests = new List<RequestEntity>();
                user.Requests.Add(request);
                unitOfWork.UserRepository.Update(user);
                unitOfWork.Save();
            }
            else
            {
                unitOfWork.RequestRepository.Add(request);
                unitOfWork.Save();
            }
            return unitOfWork.RequestRepository.FirstOrDefault(r => r.Id == request.Id).Id;
        }

        public IEnumerable<RequestEntity> GetAll()
        {
            IEnumerable<RequestEntity> requestEntitiesResult = unitOfWork.RequestRepository.GetAll();
            return requestEntitiesResult;
        }

        public IEnumerable<RequestEntity> GetAllByMail(string mail)
        {
            IEnumerable<RequestEntity> requestEntitiesAux = unitOfWork.RequestRepository.GetAll();
            IEnumerable<RequestEntity> requestEntitiesResult = requestEntitiesAux.Where(r => r.Mail == mail);
            return requestEntitiesResult;
        }

        public RequestEntity GetById(int id)
        {
            if (!unitOfWork.RequestRepository.Exists(u => u.Id == id))
                throw new ArgumentException($"Request with id: {id} does not exist");
            RequestEntity ret = unitOfWork.RequestRepository.FirstOrDefault(u => u.Id == id);
            return ret;
        }

        public void Update(RequestEntity request)
        {
            if (!unitOfWork.RequestRepository.Exists(u => u.Id == request.Id))
                throw new ArgumentException($"Request with id: {request.Id} does not exist");
            RequestStatus status = convertStringInEnum(request.Status);
            ValidateStatus(status);

            RequestEntity reqToUpdate = unitOfWork.RequestRepository.FirstOrDefault(u => u.Id == request.Id);
            reqToUpdate.Detail = request.Detail;

            RequestStatus statusToUpdate = convertStringInEnum(reqToUpdate.Status);
            StatusChange(request, status, reqToUpdate, statusToUpdate);

            unitOfWork.RequestRepository.Update(reqToUpdate);
            unitOfWork.Save();
        }

        private void StatusChange(RequestEntity request, RequestStatus status, RequestEntity reqToUpdate, RequestStatus statusToUpdate)
        {
            if (statusToUpdate != status)
            {
                if (!statusChangeIsOk(status, statusToUpdate))
                {
                    throw new ArgumentException($"Request cannot go from: {reqToUpdate.Status}, to {request.Status}");
                }
                else
                {
                    reqToUpdate.Status = request.Status.ToString();
                    if (reqToUpdate.StatusDetail == request.StatusDetail)
                        throw new ArgumentException($"If the status of a request is changed, the detail of the status must also be changed");
                    reqToUpdate.StatusDetail = request.StatusDetail;
                }
            }
            else if (reqToUpdate.StatusDetail != request.StatusDetail)
                throw new ArgumentException($"Changing the status detail is only allowed if the status is changed");
        }

        private void ValidateStatus(RequestStatus status)
        {
            if (status == RequestStatus.ERROR)
                throw new ArgumentException($"Wrong status, valid status are: CREADA, EN REVISION, ACEPTADA, DENEGADA and FINALIZADA");
        }

        public string GetRequestStatus(int requestId)
        {
            if (!unitOfWork.RequestRepository.Exists(u => u.Id == requestId))
                throw new ArgumentException($"Request with id: {requestId} does not exist");
            RequestEntity req = unitOfWork.RequestRepository.FirstOrDefault(r => r.Id == requestId);
            return req.Status;
        }

        public List<string> ReportA(string ini, string end, string email)
        {
            try
            {
                DateTime from = transformStringToDateTime(ini);
                DateTime to = transformStringToDateTime(end);

                List<string> ret = new List<string>();
                List<List<string>> aux = new List<List<string>>(5);
                if (!unitOfWork.RequestRepository.Exists(r => r.Date > from && r.Date < to && r.Mail == email))
                    throw new ArgumentException("No requests between the dates selected!");
                IEnumerable<RequestEntity> requests = unitOfWork.RequestRepository.Get(r => r.Date > from && r.Date < to);
                CreateListOfNumberOfRequestsByStateReportA(aux, requests);

                FillListOfNumberOfRequestsByStateReportA(ret, aux, 0, "Creada");
                FillListOfNumberOfRequestsByStateReportA(ret, aux, 1, "En revisión");
                FillListOfNumberOfRequestsByStateReportA(ret, aux, 2, "Aceptada");
                FillListOfNumberOfRequestsByStateReportA(ret, aux, 3, "Denegada");
                FillListOfNumberOfRequestsByStateReportA(ret, aux, 4, "Finalizada");

                return ret;
            }
            catch (ArgumentException)
            {
                throw new ArgumentException("Date format is DD-MM-YYYY HH:MM");
            }

        }

        public List<string> ReportB(string ini, string end)
        {
            try
            {
                DateTime from = transformStringToDateTime(ini);
                DateTime to = transformStringToDateTime(end);

                List<string> ret = new List<string>();
                List<Tuple<string, int>> aux = new List<Tuple<string, int>>();
                if (!unitOfWork.RequestRepository.Exists(r => r.Date > from && r.Date < to))
                    throw new ArgumentException("No requests between the dates selected!");
                IEnumerable<RequestEntity> requests = unitOfWork.RequestRepository.Get(r => r.Date > from && r.Date < to);

                CreateListOfNumberOfRequestsByStateReportB(aux, requests);
                aux = aux.OrderByDescending(t => t.Item2).ToList();
                FillListOfNumberOfRequestsByStateReportB(ret, aux);
                return ret;
            }
            catch (ArgumentException)
            {
                throw new ArgumentException("Date format is DD-MM-YYYY HH:MM");
            }
        }





        private void ValidateTypeForRequestExistance(int typeId)
        {
            if (!unitOfWork.TypeReqRepository.Exists(t => !t.IsDeleted && t.Id == typeId))
                throw new ArgumentException($"Type with id: {typeId} does not exist");
        }

        private void ValidateRequestIdExistance(int id)
        {
            if (unitOfWork.RequestRepository.Exists(u => u.Id == id))
                throw new ArgumentException($"Request with id: {id} already exist");
        }

        private void getFathersNames(RequestEntity request)
        {
            TypeReqEntity typeReq = unitOfWork.TypeReqRepository.FirstOrDefault(t => t.Id == request.RequestTypeEntityId);
            request.TypeName = typeReq.Name;
            TopicEntity topic = unitOfWork.TopicRepository.FirstOrDefault(t => t.Id == typeReq.TopicEntityId);
            request.TopicName = topic.Name;
            AreaEntity area = unitOfWork.AreaRepository.FirstOrDefault(a => a.Id == topic.AreaEntityId);
            request.AreaName = area.Name;
        }

        private string createAdditionalFieldsValues(RequestEntity r)
        {
            string ret = "";
            List<AdditionalFieldEntity> addFields = unitOfWork.AdditionalFieldRepository.Get(a => !a.IsDeleted && a.TypeReqEntityId == r.RequestTypeEntityId).ToList();
            if (addFields == null || addFields.Count == 0)
                return ret;

            string format = getAddFieldsTypes(addFields);
            string[] addFieldsArray = SplitStringToArray(r);

            ValidateFormat(r, addFields, format, addFieldsArray);

            for (int i = 0; i < addFields.Count; i++)
            {
                string value = addFieldsArray[i];
                validateValueIsInRange(value, addFields.ElementAt(i), (i + 1));
                if (i == 0) 
                    ret += addFields.ElementAt(i).Name + ": " + value;
                else 
                    ret += "-" + addFields.ElementAt(i).Name + ": " + value;
            }
            return ret;
        }

        private string[] SplitStringToArray(RequestEntity r)
        {
            string[] addFieldsArray = r.AdditionalFieldsValues.Split('-');
            return addFieldsArray;
        }

        private void ValidateFormat(RequestEntity r, List<AdditionalFieldEntity> addFields, string format, string[] addFieldsArray)
        {
            if (r.AdditionalFieldsValues == null || r.AdditionalFieldsValues == "" || addFieldsArray.Length != addFields.Count)
                throw new ArgumentException($"Field AdditionalFieldsValues must have this format: " + format);
        }

        private void validateValueIsInRange(string value, AdditionalFieldEntity addF, int i)
        {
            bool emptyRange = addF.Range == null || addF.Range.Length == 0 || (addF.Range.Length == 1 && addF.Range.Trim() == "");
            if (addF.Type != "BOOL")
            {
                string[] values = value.Split('*');
                if (values.Length > 1)
                {
                    for (int j = 0; j < values.Length; j++)
                    {
                        validateValues(values.ElementAt(j), addF, i, j + 1, emptyRange);
                    }
                } 
                else validateValues(value, addF, i, -1, emptyRange);
            }
        }

        private void validateValues(string value, AdditionalFieldEntity addF, int i, int j, bool emptyRange)
        {
            switch (addF.Type)
            {
                case "TEXTO":
                    caseText(value, addF, i, j, emptyRange);
                    break;
                case "FECHA (DD/MM/YYYY)":
                    caseDate(value, addF, i, j, emptyRange);
                    break;
                case "ENTERO":
                    caseInt(value, addF, i, j, emptyRange);
                    break;
                case "BOOL":
                    caseBool(value, addF, i, emptyRange);
                    break;
            }
        }

        private void caseBool(string value, AdditionalFieldEntity addF, int i, bool emptyRange)
        {
            if (emptyRange)
            {
                if (value.Trim().ToLower() != "true" && value.Trim().ToLower() != "false")
                    throw new ArgumentException($"Value of AdditionalFieldsValues in position {i} must be true or false");
            }
            else throw new ArgumentException($"Logic error, type bool range must be empty");
        }

        private void caseInt(string value, AdditionalFieldEntity addF, int i, int j, bool emptyRange)
        {
            try
            {
                if (emptyRange)
                    int.Parse(value);
                else
                {
                    int valueInt = int.Parse(value);
                    string[] bounds = addF.Range.Split('-');
                    int lowerBound = int.Parse(bounds.ElementAt(0));
                    int upperBound = int.Parse(bounds.ElementAt(1));
                    if (valueInt > upperBound || valueInt < lowerBound)
                        if (j == 0) throw new ArgumentException($"Value of AdditionalFieldsValues in position {i} must be between {bounds.ElementAt(0)} and {bounds.ElementAt(1)}");
                        else throw new ArgumentException($"Value of AdditionalFieldsValues in position {i} . {j} must be between {bounds.ElementAt(0)} and {bounds.ElementAt(1)}");


                }
            }
            catch (ArgumentException e) { throw new ArgumentException(e.Message); }
            catch (Exception) { throw new ArgumentException($"Value of AdditionalFieldsValues in position {i} must be of type {addF.Type}"); }
        }

        private void caseDate(string value, AdditionalFieldEntity addF, int i, int j, bool emptyRange)
        {
            try
            {
                if (emptyRange)
                {
                    string[] dateString = value.Split('/');
                    if (dateString.Length != 3) throw new Exception();
                    DateTime date = new DateTime(dateString.ElementAt(2).Length == 4 ? int.Parse(dateString.ElementAt(2)) : int.Parse(dateString.ElementAt(2)) + 2000, int.Parse(dateString.ElementAt(1)), int.Parse(dateString.ElementAt(0)));
                }
                else
                {
                    string[] bounds = addF.Range.Split('-');

                    string[] dateString = value.Split('/');
                    if (dateString.Length != 3) throw new Exception();
                    DateTime date = new DateTime(dateString.ElementAt(2).Length == 4 ? int.Parse(dateString.ElementAt(2)) : int.Parse(dateString.ElementAt(2)) + 2000, int.Parse(dateString.ElementAt(1)), int.Parse(dateString.ElementAt(0)));

                    string[] dateLowerString = bounds.ElementAt(0).ToString().Split('/');
                    DateTime datelower = new DateTime(dateLowerString.ElementAt(2).Length == 4 ? int.Parse(dateLowerString.ElementAt(2)) : int.Parse(dateLowerString.ElementAt(2)) + 2000, int.Parse(dateLowerString.ElementAt(1)), int.Parse(dateLowerString.ElementAt(0)));

                    string[] dateUpperString = bounds.ElementAt(1).ToString().Split('/');
                    DateTime dateUpper = new DateTime(dateUpperString.ElementAt(2).Length == 4 ? int.Parse(dateUpperString.ElementAt(2)) : int.Parse(dateUpperString.ElementAt(2)) + 2000, int.Parse(dateUpperString.ElementAt(1)), int.Parse(dateUpperString.ElementAt(0)));

                    if (date > dateUpper || date < datelower) 
                        if(j == -1) throw new ArgumentException($"Value of AdditionalFieldsValues in position {i} must be between {bounds.ElementAt(0)} and {bounds.ElementAt(1)}");
                    else throw new ArgumentException($"Value of AdditionalFieldsValues in position {i} . {j} must be between {bounds.ElementAt(0)} and {bounds.ElementAt(1)}");
                }
            }
            catch (ArgumentException e) { throw new ArgumentException(e.Message); }
            catch (Exception) { 
                if(j == -1) throw new ArgumentException($"Value of AdditionalFieldsValues in position {i} must have the following format: DD/MM/YYYY");
                else throw new ArgumentException($"Value of AdditionalFieldsValues in position {i} . {j} must have the following format: DD/MM/YYYY");
            }
        }

        private void caseText(string value, AdditionalFieldEntity addF, int i, int x, bool emptyRange)
        {
            if (!emptyRange)
            {
                string[] range = addF.Range.Split('-');
                if (!range.Contains(value))
                {
                    string list = "[ ";
                    for (int j = 0; j < range.Length; j++)
                    {
                        if (j == 0) list += range.ElementAt(j);
                        else if (j == range.Length - 1) list += ", " + range.ElementAt(j) + " ]";
                        else list += ", " + range.ElementAt(j);
                    }
                    if(x==-1) throw new ArgumentException($"Value of AdditionalFieldsValues in position {i} must be in this list: {list}");
                    else throw new ArgumentException($"Value of AdditionalFieldsValues in position {i} . {x} must be in this list: {list}");
                }
            }
        }

        private string getAddFieldsTypes(List<AdditionalFieldEntity> addFields)
        {
            string ret = "";
            for (int i = 0; i < addFields.Count; i++)
            {
                if (addFields.ElementAt(i).Type == "FECHA") addFields.ElementAt(i).Type = "FECHA (DD/MM/YYYY)";
                if (addFields.Count == 1) return ret + addFields.ElementAt(i).Type;
                if (i == 0) ret += addFields.ElementAt(i).Type;
                else if (i == addFields.Count - 1) ret += "-" + addFields.ElementAt(i).Type;
                else ret += "-" + addFields.ElementAt(i).Type;
            }
            return ret;
        }

        private RequestStatus convertStringInEnum(string status)
        {
            string statusOk = status.ToUpper().Trim();
            switch (statusOk)
            {
                case "CREADA":
                    return RequestStatus.CREADA;
                case "ENREVISION":
                    return RequestStatus.ENREVISION;
                case "EN REVISION":
                    return RequestStatus.ENREVISION;
                case "ACEPTADA":
                    return RequestStatus.ACEPTADA;
                case "DENEGADA":
                    return RequestStatus.DENEGADA;
                case "FINALIZADA":
                    return RequestStatus.FINALIZADA;
            }
            throw new ArgumentException($"Wrong status. Valid status are: creada, enrevision, aceptada, denegada and finalizada");
        }

        private bool statusChangeIsOk(RequestStatus from, RequestStatus to)
        {
            switch (from) {
                case RequestStatus.CREADA:
                    if (to == RequestStatus.ENREVISION) return true;
                    return false;
                case RequestStatus.ENREVISION:
                    if (to == RequestStatus.CREADA || to == RequestStatus.ACEPTADA || to == RequestStatus.DENEGADA) return true;
                    return false;
                case RequestStatus.ACEPTADA:
                    if (to == RequestStatus.ENREVISION || to == RequestStatus.FINALIZADA || to == RequestStatus.DENEGADA) return true;
                    return false;
                case RequestStatus.DENEGADA:
                    if (to == RequestStatus.ENREVISION || to == RequestStatus.FINALIZADA || to == RequestStatus.ACEPTADA) return true;
                    return false;
                case RequestStatus.FINALIZADA:
                    if (to == RequestStatus.DENEGADA || to == RequestStatus.ACEPTADA) return true;
                    return false;
                case RequestStatus.ERROR:
                    return false;
                default:
                    return false;
            }
        }

        private DateTime transformStringToDateTime(string date)
        {
            if(date == "") throw new Exception();
            string[] aux = date.Split(' ');
            if(aux.Length != 2 || aux[0] == "" || aux[1] == "") throw new Exception();
            string date2 = aux[0];
            string hour = aux[1];

            string[] dateString = date2.Split('-');
            if (dateString.Length != 3) throw new Exception();

            string[] hourString = hour.Split(':');
            if (hourString.Length != 2) throw new Exception();

            return new DateTime(int.Parse(dateString.ElementAt(2)), int.Parse(dateString.ElementAt(1)), int.Parse(dateString.ElementAt(0)), int.Parse(hourString.ElementAt(0)), int.Parse(hourString.ElementAt(1)), 0);
        }

        private void FillListOfNumberOfRequestsByStateReportA(List<string> ret, List<List<string>> aux, int number, string state)
        {
            if (aux.ElementAt(number) != null && aux.ElementAt(number).Count > 0)
            {
                List<string> requestsInState = aux.ElementAt(number);
                string toAdd = state + " (" + requestsInState.Count() + ") = [";
                if (requestsInState.Count() == 1) toAdd += requestsInState.ElementAt(0) + "]";
                else
                {
                    for (int i = 0; i < requestsInState.Count(); i++)
                    {
                        if (i == 0) toAdd += requestsInState.ElementAt(i);
                        else if (i == requestsInState.Count() - 1) toAdd += ", " + requestsInState.ElementAt(i) + " ]";
                        else toAdd += ", " + requestsInState.ElementAt(i);
                    }
                }
                ret.Add(toAdd);
            }
        }

        private void CreateListOfNumberOfRequestsByStateReportA(List<List<string>> aux, IEnumerable<RequestEntity> requests)
        {
            for (int i = 0; i < 5; i++)
            {
                aux.Add(new List<string>());
            }
            for (int i = 0; i < requests.Count(); i++)
            {
                switch (requests.ElementAt(i).Status)
                {
                    case "CREADA":
                        aux[0].Add(requests.ElementAt(i).Id.ToString());
                        break;
                    case "ENREVISION":
                        aux[1].Add(requests.ElementAt(i).Id.ToString());
                        break;
                    case "ACEPTADA":
                        aux[2].Add(requests.ElementAt(i).Id.ToString());
                        break;
                    case "DENEGADA":
                        aux[3].Add(requests.ElementAt(i).Id.ToString());
                        break;
                    case "FINALIZADA":
                        aux[4].Add(requests.ElementAt(i).Id.ToString());
                        break;
                }
            }
        }

        private void FillListOfNumberOfRequestsByStateReportB(List<string> ret, List<Tuple<string, int>> aux)
        {
            for (int i = 0; i < aux.Count(); i++)
            {
                ret.Add(aux.ElementAt(i).Item1 + " (" + aux.ElementAt(i).Item2 + ")");
            }
        }

        private void CreateListOfNumberOfRequestsByStateReportB(List<Tuple<string, int>> aux, IEnumerable<RequestEntity> requests)
        {
            for (int i = 0; i < requests.Count(); i++)
            {
                RequestEntity request = requests.ElementAt(i);
                var tuple = aux.FirstOrDefault(t => t.Item1 == request.TypeName);
                if (tuple != default)
                {
                    Tuple<string, int> toAdd = new Tuple<string, int>(tuple.Item1, tuple.Item2 + 1);
                    aux[aux.IndexOf(tuple)] = toAdd;
                }
                else
                {
                    Tuple<string, int> toAdd = new Tuple<string, int>(request.TypeName, 1);
                    aux.Add(toAdd);
                }
            }
        }
    }

}
