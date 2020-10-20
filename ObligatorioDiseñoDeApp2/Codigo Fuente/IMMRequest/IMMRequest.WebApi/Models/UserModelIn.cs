﻿using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json.Serialization;
using System.ComponentModel.DataAnnotations;


namespace IMMRequest.WebApi.Models
{
    public class UserModelIn
    {
        public int Id { get; set; }
        [Required]
        public string CompleteName { get; set; }
        [Required]
        [DataType(DataType.EmailAddress)]
        [EmailAddress]
        public string Mail { get; set; }
        [Required]
        public string Password { get; set; }
        [Required]
        public bool IsAdmin { get; set; }
    }
}