using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace IMMRequest.WebApi.Models
{
    public class LoginModelIn
    {
        public LoginModelIn() { }
        
        public LoginModelIn(string mail, string password)
        {
            Mail = mail;
            Password = password;
        }

        [Required]
        public string Mail { get; set; }

        [Required]
        public string Password { get; set; }
    }
}
