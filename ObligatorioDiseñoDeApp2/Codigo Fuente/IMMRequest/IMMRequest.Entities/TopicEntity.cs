using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;

namespace IMMRequest.Entities
{
    public class TopicEntity
    {
        public TopicEntity() { }
        public int Id { get; set; }
        public string Name { get; set; }
        public int AreaEntityId { get; set; }
        public ICollection<TypeReqEntity> RequestTypes { get; set; }

        public override bool Equals(object objectReceived)
        {
            bool objectsAreEqual = false;
            if (objectReceived != null && objectReceived.GetType().Equals(this.GetType()))
            {
                TopicEntity topicBeingCompared = (TopicEntity)objectReceived;
                objectsAreEqual = Id.Equals(topicBeingCompared.Id);
            }
            return objectsAreEqual;
        }
    }
}