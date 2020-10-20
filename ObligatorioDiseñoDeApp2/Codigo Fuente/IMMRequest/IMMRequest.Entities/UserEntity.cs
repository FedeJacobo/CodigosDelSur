using System;
using System.Collections.Generic;

namespace IMMRequest.Entities
{
    public class UserEntity
    {
        public UserEntity() { }
        public int Id { get; set; }
        public string CompleteName { get; set; }
        public string Mail { get; set; }
        public string Password { get; set; }
        public ICollection<RequestEntity> Requests { get; set; }
        public bool IsAdmin { get; set; }
        public bool IsDeleted { get; set; }

        public override bool Equals(object objectReceived)
        {
            bool objectsAreEqual = false;
            if (objectReceived != null && objectReceived.GetType().Equals(this.GetType()))
            {
                UserEntity userBeingCompared = (UserEntity)objectReceived;
                objectsAreEqual = Id.Equals(userBeingCompared.Id);
            }
            return objectsAreEqual;
        }
    }
}
