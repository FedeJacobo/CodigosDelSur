using System.Collections.Generic;

namespace IMMRequest.Entities
{
    public class AreaEntity
    {
        public AreaEntity() { }
        public int Id { get; set; }
        public string Name { get; set; }
        public ICollection<TopicEntity> Topics { get; set; }

        public override bool Equals(object objectReceived)
        {
            bool objectsAreEqual = false;
            if (objectReceived != null && objectReceived.GetType().Equals(this.GetType()))
            {
                AreaEntity areaBeingCompared = (AreaEntity)objectReceived;
                objectsAreEqual = Id.Equals(areaBeingCompared.Id);
            }
            return objectsAreEqual;
        }
    }
}