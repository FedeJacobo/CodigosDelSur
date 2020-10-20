using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace IMMRequest.WebApi.Models
{
    public class ImportModelIn
    {
        [Required]
        public string Name { get; set; }
        public ICollection<ParameterModelIn> Parameters { get; set; }
    }
}
