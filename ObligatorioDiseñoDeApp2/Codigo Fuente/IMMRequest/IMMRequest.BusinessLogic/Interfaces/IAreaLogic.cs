using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.BusinessLogic.Interfaces
{
    public interface IAreaLogic
    {
        int Add(AreaEntity area);
        IEnumerable<AreaEntity> GetAll();
        AreaEntity GetByName(string name);
    }
}
