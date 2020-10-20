using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace IMMRequest.WebApi.Models
{
    public class RequestModelOut
    {
        public int Id { get; set; }
        [Required]
        public string Detail { get; set; }
        [Required]
        public string ApplicantName { get; set; }
        [Required]
        public string Mail { get; set; }
        [Required]
        public string Status { get; set; }
        [Required]
        public string StatusDetail { get; set; }
        public string Phone { get; set; }
        [Required]
        public int RequestTypeEntityId { get; set; }
        [Required]
        public string AdditionalFieldsValues { get; set; }
        [Required]
        public string AreaName { get; set; }
        [Required]
        public string TopicName { get; set; }
        [Required]
        public string TypeName { get; set; }
    }
}
