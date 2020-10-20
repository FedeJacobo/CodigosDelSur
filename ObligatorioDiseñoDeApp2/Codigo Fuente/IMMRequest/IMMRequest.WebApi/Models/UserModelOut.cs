using System.ComponentModel.DataAnnotations;

namespace IMMRequest.WebApi.Models
{
    public class UserModelOut
    {
        public int Id { get; set; }
        [Required]
        public string CompleteName { get; set; }
        [Required]
        public string Mail { get; set; }
        [Required]
        public string Password { get; set; }
        [Required]
        public bool IsAdmin { get; set; }
    }
}
