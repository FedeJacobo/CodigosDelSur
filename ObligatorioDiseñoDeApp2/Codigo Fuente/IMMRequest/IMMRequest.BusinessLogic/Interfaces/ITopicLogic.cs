using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.BusinessLogic.Interfaces
{
    public interface ITopicLogic
    {
        int Add(TopicEntity topic);
        IEnumerable<TopicEntity> GetAll();
        TopicEntity GetByName(string name);
    }
}
