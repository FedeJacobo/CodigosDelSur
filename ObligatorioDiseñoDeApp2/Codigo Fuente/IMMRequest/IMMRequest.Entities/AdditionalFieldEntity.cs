using System.Collections.Generic;

namespace IMMRequest.Entities
{
    public class AdditionalFieldEntity
    {
        public AdditionalFieldEntity() { }
        public int Id { get; set; }
        public string Name { get; set; }
        public string Type { get; set; }
        public string Range { get; set; }
        public int TypeReqEntityId { get; set; }
        public bool IsDeleted { get; set; }

        public override bool Equals(object objectReceived)
        {
            bool objectsAreEqual = false;
            if (objectReceived != null && objectReceived.GetType().Equals(this.GetType()))
            {
                AdditionalFieldEntity afBeingCompared = (AdditionalFieldEntity)objectReceived;
                objectsAreEqual = Id.Equals(afBeingCompared.Id);
            }
            return objectsAreEqual;
        }
    }
}