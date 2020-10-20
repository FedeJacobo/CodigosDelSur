using System.Collections.Generic;

namespace IMMRequest.Entities
{
    public class TypeReqEntity
    {
        public TypeReqEntity() { }
        public int Id { get; set; }
        public string Name { get; set; }
        public ICollection<AdditionalFieldEntity> AdditionalFields { get; set; }
        public int TopicEntityId { get; set; }
        public bool IsDeleted { get; set; }

        public override bool Equals(object objectReceived)
        {
            bool objectsAreEqual = false;
            if (objectReceived != null && objectReceived.GetType().Equals(this.GetType()))
            {
                TypeReqEntity typeReqBeingCompared = (TypeReqEntity)objectReceived;
                objectsAreEqual = Id.Equals(typeReqBeingCompared.Id);
            }
            return objectsAreEqual;
        }
    }
}