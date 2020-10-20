using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.IDataImporter
{
    public interface IGenericImporter
    {
        ICollection<AreaEntity> GetAreas(ICollection<Parameter> parameters);
        ICollection<TopicEntity> GetTopics(ICollection<Parameter> parameters);
        ICollection<TypeReqEntity> GetTypeReqs(ICollection<Parameter> parameters);
        string GetName();
        ICollection<string> GetTypeParameters();
    }
}
