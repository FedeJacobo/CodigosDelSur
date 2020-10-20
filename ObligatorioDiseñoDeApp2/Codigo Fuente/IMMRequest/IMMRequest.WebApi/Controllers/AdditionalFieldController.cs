using AutoMapper;
using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.Entities;
using IMMRequest.WebApi.Filters;
using IMMRequest.WebApi.Mapper;
using IMMRequest.WebApi.Models;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;

namespace IMMRequest.WebApi.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class AdditionalFieldController : ControllerBase
    {
        private IAdditionalFieldLogic additionalFieldLogic;
        private IMapper mapper;

        public AdditionalFieldController(IAdditionalFieldLogic additionalFieldLogic, IWebApiMapper apiMapper)
        {
            this.mapper = apiMapper.Configure();
            this.additionalFieldLogic = additionalFieldLogic;
        }

        [HttpGet]
        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        public ActionResult Get()
        {
            IEnumerable<AdditionalFieldEntity> additionalFields;
            try
            {
                additionalFields = additionalFieldLogic.GetAll();
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            var additionalFieldOut = mapper.Map<IEnumerable<AdditionalFieldEntity>, IEnumerable<AdditionalFieldModelOut>>(additionalFields);
            return this.Ok(additionalFieldOut);
        }

        [HttpPost]
        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        public IActionResult Post([FromBody] AdditionalFieldModelIn additionalFieldIn)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    var additionalField = mapper.Map<AdditionalFieldModelIn, AdditionalFieldEntity>(additionalFieldIn);

                    var id = additionalFieldLogic.Add(additionalField);
                    var addedAdditionalField = additionalFieldLogic.GetById(id);
                    var addedAdditionalFieldOut = mapper.Map<AdditionalFieldEntity, AdditionalFieldModelOut>(addedAdditionalField);
                    return Created("Posted succesfully", addedAdditionalFieldOut);
                }
                catch (Exception ex)
                {
                    return BadRequest(ex.Message);
                }
            }
            else
            {
                return BadRequest(ModelState);
            }
        }

        [HttpGet("{id}")]
        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        public ActionResult Get(int id)
        {
            AdditionalFieldEntity additionalField;
            try
            {
                additionalField = additionalFieldLogic.GetById(id);
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            var additionalFieldOut = mapper.Map<AdditionalFieldEntity, AdditionalFieldModelOut>(additionalField);
            return this.Ok(additionalFieldOut);
        }
    }
}
