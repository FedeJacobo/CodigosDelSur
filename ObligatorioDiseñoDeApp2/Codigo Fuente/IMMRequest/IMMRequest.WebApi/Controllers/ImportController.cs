using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using AutoMapper;
using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.Entities;
using IMMRequest.IDataImporter;
using IMMRequest.WebApi.Mapper;
using IMMRequest.WebApi.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;

namespace IMMRequest.WebApi.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ImportController : ControllerBase
    {
        private IImportLogic importLogic;
        private IMapper mapper;
        private readonly IConfiguration configuration;
        public ImportController(IImportLogic importLogic, IWebApiMapper apiMapper, IConfiguration configuration)
        {
            this.mapper = apiMapper.Configure();
            this.importLogic = importLogic;
            this.configuration = configuration;
        }

        [HttpPost("import")]
        public IActionResult Import([FromBody] ImportModelIn importModelIn)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    var parameters = mapper.Map<ICollection<ParameterModelIn>, ICollection<Parameter>>(importModelIn.Parameters);
                    var imported = importLogic.ImportEverything(importModelIn.Name, parameters);
                    return this.Ok(imported);
                }
                catch (ArgumentException ex)
                {
                    return BadRequest(ex.Message);
                }
            }
            else
            {
                return BadRequest(ModelState);
            }
        }

        [HttpGet("import/{nameImporter}")]
        public IActionResult GetParameterNamesFromImporter(string importer)
        {
            try
            {
                var parameterNames = importLogic.GetParameterNames(importer);
                return Ok(parameterNames);
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
        }

        [HttpGet("import")]
        public IActionResult GetImportersNames()
        {
            string[] filesArray = Directory.GetFiles(@".\\Assemblies", "*.dll");
            if (filesArray != null)
            {
                for(int i = 0; i < filesArray.Length; i++)
                {
                    filesArray[i] = filesArray[i].Substring(14);
                }
                return Ok(filesArray);
            }
            else
            {
                return BadRequest("There are no importers available");
            }
        }
    }
}
