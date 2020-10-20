using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Linq;

namespace IMMRequest.BusinessLogic
{
    public class AdditionalFieldLogic: IAdditionalFieldLogic
    {
        private IUnitOfWork unitOfWork;

        public AdditionalFieldLogic(IUnitOfWork unitOfWork)
        {
            this.unitOfWork = unitOfWork;
        }

        public int Add(AdditionalFieldEntity additionalField)
        {
            ValidateTypeReqExistance(additionalField.TypeReqEntityId);
            ValidateExistanceInType(additionalField);
            ValidateAdditionalFieldType(additionalField.Type);
            ValidateRangeFromType(additionalField);
            unitOfWork.AdditionalFieldRepository.Add(additionalField);
            unitOfWork.Save();
            return unitOfWork.AdditionalFieldRepository.FirstOrDefault(a => !additionalField.IsDeleted 
            && a.Name == additionalField.Name && additionalField.TypeReqEntityId == additionalField.TypeReqEntityId).Id;
        }

        private void ValidateAdditionalFieldType(string additionalFieldType)
        {
            if (additionalFieldType == AdditionalFieldType.ERROR.ToString())
                throw new ArgumentException($"Wrong type, valid tipes are TEXTO, ENTERO, FECHA and BOOL");
        }

        private void ValidateExistanceInType(AdditionalFieldEntity additionalField)
        {
            if (unitOfWork.AdditionalFieldRepository.Exists(a => !a.IsDeleted && a.Name == additionalField.Name &&
            a.TypeReqEntityId == additionalField.TypeReqEntityId))
                throw new ArgumentException($"There is already an AdditionalField with name {additionalField.Name} " +
                    $"in the Type " + $"with id: {additionalField.TypeReqEntityId}");
        }

        private void ValidateTypeReqExistance(int typeId)
        {
            if (!unitOfWork.TypeReqRepository.Exists(t => !t.IsDeleted && t.Id == typeId))
                throw new ArgumentException($"Type with id: {typeId} does not exist");
        }

        private void ValidateRangeFromType(AdditionalFieldEntity additionalField)
        {
            string[] rangeArray = SplitStringToArray(additionalField);
            if (additionalField.Range == "" || rangeArray.Length == 0) return;
            switch (additionalField.Type)
            {
                case "ENTERO":
                    numberCase(additionalField, rangeArray);
                    break;
                case "FECHA":
                    dateCase(additionalField, rangeArray);
                    break;
                case "BOOL":
                    boolCase(additionalField, rangeArray);
                    break;
            }
        }

        private string[] SplitStringToArray(AdditionalFieldEntity additionalField)
        {
            string[] addFieldsArray = additionalField.Range.Split('-');
            return addFieldsArray;
        }

        private void boolCase(AdditionalFieldEntity additionalField, string[] rangeArray)
        {
            if (additionalField.Range == null || additionalField.Range == "" || 
                rangeArray.Length == 0 || (rangeArray.Length == 1 && rangeArray[0].Trim() == "")) return;
            else 
                throw new ArgumentException($"Bool type does not accept values, it can only be true or false");
        }

        private void dateCase(AdditionalFieldEntity additionalField, string[] rangeArray)
        {
            if (additionalField.Range == null || additionalField.Range == "" ||
                rangeArray.Length == 0 || (rangeArray.Length == 1 && rangeArray[0].Trim() == "")) return;
            if (rangeArray.Length != 2)
                throw new ArgumentException($"Date type must be made up of two dates: a lower bound and an upper bound");
            else
            {
                try
                {
                    DateTime lowerDate, upperDate;
                    validateCorrectDates(additionalField, out lowerDate, out upperDate);

                    if (lowerDate > upperDate)
                        throw new ArgumentException($"The first date must occur before the second");
                }
                catch (ArgumentException e) { throw new ArgumentException(e.Message); }
                catch (Exception) { throw new ArgumentException($"All elements of a date type range must have the following format: DD/MM/YYYY"); }
            }
        }

        private void numberCase(AdditionalFieldEntity additionalField, string[] rangeArray)
        {
            if (additionalField.Range == null || additionalField.Range == "" ||
                rangeArray.Length == 0 || (rangeArray.Length == 1 && rangeArray[0].Trim() == "")) return;
            if (rangeArray.Length != 2)
                throw new ArgumentException($"Numerical ranges must be made up of two numbers: a lower bound and an upper bound");
            else
            {
                try
                {
                    int lowerBound = int.Parse(rangeArray[0]);
                    int upperBound = int.Parse(rangeArray[1]);
                    if (lowerBound > upperBound)
                        throw new ArgumentException($"The first element of the range must be smaller or equal to the second");
                }
                catch (ArgumentException e) { throw new ArgumentException(e.Message); }
                catch (Exception) { throw new ArgumentException($"All elements of a numerical range must be of numeric type"); }
            }
        }

        private void validateCorrectDates(AdditionalFieldEntity additionalField, out DateTime lowerDate, out DateTime upperDate)
        {
            string[] arrayForFirstDate = additionalField.Range.Split('-');
            string[] lowerDateString = arrayForFirstDate[0].Split('/');
            if (lowerDateString.Length != 3) throw new Exception();
            int lowerDay = int.Parse(lowerDateString.ElementAt(0));
            int lowerMonth = int.Parse(lowerDateString.ElementAt(1));
            int lowerYear = lowerDateString.ElementAt(2).Length == 4? int.Parse(lowerDateString.ElementAt(2)) : 2000 + int.Parse(lowerDateString.ElementAt(2));
            lowerDate = new DateTime(lowerYear, lowerMonth, lowerDay);

            string[] arrayForSecondDate = additionalField.Range.Split('-');
            string[] upperDateString = arrayForFirstDate[1].Split('/');
            if (upperDateString.Length != 3) throw new Exception();
            int upperDay = int.Parse(upperDateString.ElementAt(0));
            int upperMonth = int.Parse(upperDateString.ElementAt(1));
            int upperYear = upperDateString.ElementAt(2).Length == 4 ? int.Parse(upperDateString.ElementAt(2)) : 2000 + int.Parse(upperDateString.ElementAt(2));
            upperDate = new DateTime(upperYear, upperMonth, upperDay);
        }

        public AdditionalFieldEntity GetById(int id)
        {
            ValidateAdditionalFieldIdExistance(id);
            AdditionalFieldEntity ret = unitOfWork.AdditionalFieldRepository.FirstOrDefault(u => !u.IsDeleted && u.Id == id);
            return ret;
        }

        private void ValidateAdditionalFieldIdExistance(int id)
        {
            if (!unitOfWork.AdditionalFieldRepository.Exists(a => !a.IsDeleted && a.Id == id))
                throw new ArgumentException($"Additional field with Id: {id} doesn't exist");
        }

        private ICollection<string> convertStringInList(string range)
        {
            if (range != null) {
                return range.Split(("-").ToCharArray());
            }
            else
            {
                return new List<string>();
            }
            
        }

        public AdditionalFieldEntity GetByName(string name)
        {
            ValidateAdditionalFieldNameExistance(name);
            AdditionalFieldEntity ret = unitOfWork.AdditionalFieldRepository.FirstOrDefault(u => !u.IsDeleted && u.Name == name);
            return ret;
        }

        private void ValidateAdditionalFieldNameExistance(string name)
        {
            if (!unitOfWork.AdditionalFieldRepository.Exists(a => !a.IsDeleted && a.Name == name))
                throw new ArgumentException($"Additional field with name: {name} doesn't exist");
        }

        public IEnumerable<AdditionalFieldEntity> GetAll()
        {
            IEnumerable<AdditionalFieldEntity> additionalFields = unitOfWork.AdditionalFieldRepository.GetAll().Where(x => !x.IsDeleted).ToList();
            return additionalFields;
        }
    }
}
