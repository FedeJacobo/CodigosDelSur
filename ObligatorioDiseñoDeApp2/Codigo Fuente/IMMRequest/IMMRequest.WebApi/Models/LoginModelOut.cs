using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace IMMRequest.WebApi.Models
{
    public class LoginModelOut
    {
        [Required]
        public string Mail { get; set; }
        [Required]
        public Guid Token { get; set; }
        [Required]
        public bool IsAdmin { get; set; }
    }
}
