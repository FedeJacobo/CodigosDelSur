using System.ComponentModel.DataAnnotations;

namespace IMMRequest.WebApi.Models
{
    public class TypeReqModelIn
    {
        public int Id { get; set; }
        [Required]
        public string Name { get; set; }
        [Required]
        public int TopicEntityId { get; set; }
    }
}
