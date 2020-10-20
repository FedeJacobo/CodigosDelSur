using AutoMapper;
using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.Entities;
using IMMRequest.WebApi.Filters;
using IMMRequest.WebApi.Mapper;
using IMMRequest.WebApi.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;

namespace IMMRequest.WebApi.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TypeReqController : ControllerBase
    {
        private ITypeReqLogic typeReqLogic;
        private IMapper mapper;

        public TypeReqController(ITypeReqLogic typeReqLogic, IWebApiMapper apiMapper)
        {
            this.mapper = apiMapper.Configure();
            this.typeReqLogic = typeReqLogic;
        }

        [HttpGet]
        [AllowAnonymous]
        public ActionResult Get()
        {
            IEnumerable<TypeReqEntity> typeReqs;
            try
            {
                typeReqs = typeReqLogic.GetAll();
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            var typeReqsOut = mapper.Map<IEnumerable<TypeReqEntity>, IEnumerable<TypeReqModelOut>>(typeReqs);
            return this.Ok(typeReqsOut);
        }

        [HttpPost]
       [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        public IActionResult Post([FromBody] TypeReqModelIn typeReqIn)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    var type = mapper.Map<TypeReqModelIn, TypeReqEntity>(typeReqIn);
                    var id = typeReqLogic.Add(type);
                    var addedType = typeReqLogic.GetByName(type.Name);
                    var addedTypeOut = mapper.Map<TypeReqEntity, TypeReqModelOut>(addedType);
                    return Created("Posted succesfully", addedTypeOut);
                }
                catch (ArgumentException ex)
                {
                    return BadRequest(ex.Message);
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
        [AllowAnonymous]
        public ActionResult Get(int id)
        {
            TypeReqEntity typeReq;
            try
            {
                typeReq = typeReqLogic.GetById(id);
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            var requestOut = mapper.Map<TypeReqEntity, TypeReqModelOut>(typeReq);
            return this.Ok(requestOut);
        }

        [HttpPut("{id}")]
        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        public IActionResult Put(int id, [FromBody] TypeReqModelIn typeReqIn)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    typeReqIn.Id = id;
                    var typeReq = mapper.Map<TypeReqModelIn, TypeReqEntity>(typeReqIn);
                    typeReqLogic.Update(typeReq);
                    var updatedTypeReq = typeReqLogic.GetById(id);
                    var updatedTypeReqModelOut = mapper.Map<TypeReqEntity, TypeReqModelOut>(updatedTypeReq);
                    return Created("Put succesfully", updatedTypeReqModelOut);
                }
                catch (ArgumentException e)
                {
                    return (BadRequest(e.Message));
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

        [HttpDelete("{id}")]
        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        public IActionResult Delete(int id)
        {
            try
            {
                typeReqLogic.Delete(id);
                return this.Ok();
            }
            catch (ArgumentException e)
            {
                return BadRequest(e.Message);
            }
            catch (Exception e)
            {
                return BadRequest(e.Message);
            }
        }

        [AllowAnonymous]
        [HttpGet("{id}/additionalField")]
        public ActionResult GetAdditionalFields(int id)
        {
            IEnumerable<AdditionalFieldEntity> addFs;
            try
            {
                addFs = typeReqLogic.GetAdditionalFields(id);
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            var addFsOut = mapper.Map<IEnumerable<AdditionalFieldEntity>, IEnumerable<AdditionalFieldModelOut>>(addFs);
            return this.Ok(addFsOut);
        }
    }
}
