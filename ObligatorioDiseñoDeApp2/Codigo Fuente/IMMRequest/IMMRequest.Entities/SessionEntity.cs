using System;

namespace IMMRequest.Entities
{
    public class SessionEntity
    {
        public Guid Id { get; set; }
        public Guid Token { get; set; }
        public int AdminId { get; set; }
        public string Mail { get; set; }

        public SessionEntity()
        {
            Id = Guid.NewGuid();
        }
    }
}
