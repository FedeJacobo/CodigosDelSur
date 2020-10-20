using IMMRequest.Entities;
using System.Collections.Generic;

namespace IMMRequest.BusinessLogic.Interfaces
{
    public interface ITypeReqLogic
    {
        int Add(TypeReqEntity tr);
        IEnumerable<TypeReqEntity> GetAll();
        TypeReqEntity GetById(int id);
        TypeReqEntity GetByName(string name);
        void Delete(int id);
        void Update(TypeReqEntity tr);
        IEnumerable<AdditionalFieldEntity> GetAdditionalFields(int typeId);
    }
}
