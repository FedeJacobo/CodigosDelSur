
using System;
using System.Collections.Generic;

namespace IMMRequest.Entities
{
    public class RequestEntity
    {
        public RequestEntity() { }
        public int Id { get; set; }
        public string Detail { get; set; }
        public string ApplicantName { get; set; }
        public string Mail { get; set; }
        public string Phone { get; set; }
        public int RequestTypeEntityId { get; set; }
        public string Status { get; set; }
        public string StatusDetail { get; set; }
        public string AdditionalFieldsValues { get; set; }
        public string AreaName { get; set; }
        public string TopicName { get; set; }
        public string TypeName { get; set; }
        public DateTime Date { get; set; }

        public override bool Equals(object objectReceived)
        {
            bool objectsAreEqual = false;
            if (objectReceived != null && objectReceived.GetType().Equals(this.GetType()))
            {
                RequestEntity requestBeingCompared = (RequestEntity)objectReceived;
                objectsAreEqual = Id.Equals(requestBeingCompared.Id);
            }
            return objectsAreEqual;
        }
    }
}