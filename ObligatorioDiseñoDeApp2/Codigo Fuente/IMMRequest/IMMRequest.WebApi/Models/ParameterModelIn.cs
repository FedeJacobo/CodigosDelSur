using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace IMMRequest.WebApi.Models
{
    public class ParameterModelIn
    {
        [Required]
        public string Name { get; set; }
        [Required]
        public string Value { get; set; }
    }
}
