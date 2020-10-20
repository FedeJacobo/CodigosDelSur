using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace IMMRequest.WebApi.Models
{
    public class RequestModelIn
    {
        public int Id { get; set; }
        [Required]
        [StringLength(2000, ErrorMessage = "The detail value cannot exceed 2000 characters. ")]
        public string Detail { get; set; }
        [Required]
        public string ApplicantName { get; set; }
        [Required]
        [DataType(DataType.EmailAddress)]
        [EmailAddress]
        public string Mail { get; set; }
        [Required]
        public string Status { get; set; }
        [Required]
        public string StatusDetail { get; set; }
        public string Phone { get; set; }
        [Required]
        public int RequestTypeEntityId { get; set; }
        public string AdditionalFieldsValues { get; set; }
    }
}
