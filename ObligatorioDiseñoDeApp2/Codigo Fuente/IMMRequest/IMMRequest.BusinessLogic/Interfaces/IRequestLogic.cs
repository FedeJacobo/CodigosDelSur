using IMMRequest.Entities;
using System.Collections.Generic;

namespace IMMRequest.BusinessLogic.Interfaces
{
    public interface IRequestLogic
    {
        int Add(RequestEntity request);
        IEnumerable<RequestEntity> GetAll();
        IEnumerable<RequestEntity> GetAllByMail(string mail);
        RequestEntity GetById(int id);
        void Update(RequestEntity request);
        string GetRequestStatus(int requestId);
        List<string> ReportA(string ini, string end, string email);
        List<string> ReportB(string ini, string end);
    }
}
