using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace IMMRequest.WebApi.Models
{
    public class AreaModelOut
    {
        public int Id { get; set; }
        [Required]
        public string Name { get; set; }
    }
}
