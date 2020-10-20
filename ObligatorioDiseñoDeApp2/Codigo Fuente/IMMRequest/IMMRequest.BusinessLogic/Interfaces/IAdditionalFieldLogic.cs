using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.BusinessLogic.Interfaces
{
    public interface IAdditionalFieldLogic
    {
        int Add(AdditionalFieldEntity af);
        IEnumerable<AdditionalFieldEntity> GetAll();
        AdditionalFieldEntity GetById(int id);
        AdditionalFieldEntity GetByName(string name);
    }
}
