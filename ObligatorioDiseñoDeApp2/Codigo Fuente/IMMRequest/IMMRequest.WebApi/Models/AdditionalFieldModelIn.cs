using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace IMMRequest.WebApi.Models
{
    public class AdditionalFieldModelIn
    {
        public int Id { get; set; }
        [Required]
        public string Name { get; set; }
        [Required]
        public string Type { get; set; }
        public string Range{ get; set; }
        [Required]
        public int TypeReqEntityId { get; set; }
    }
}
