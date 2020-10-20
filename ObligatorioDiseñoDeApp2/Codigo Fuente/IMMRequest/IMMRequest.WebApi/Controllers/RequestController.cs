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
    public class RequestController : ControllerBase
    {
        private IRequestLogic requestLogic;
        private IMapper mapper;

        public RequestController(IRequestLogic requestLogic, IWebApiMapper apiMapper)
        {
            this.mapper = apiMapper.Configure();
            this.requestLogic = requestLogic;
        }

        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        [HttpGet]
        public ActionResult Get()
        {
            IEnumerable<RequestEntity> requests;
            try
            {
                requests = requestLogic.GetAll();
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            var requestsOut = mapper.Map<IEnumerable<RequestEntity>, IEnumerable<RequestModelOut>>(requests);
            return this.Ok(requestsOut);
        }

        [HttpPost]
        [AllowAnonymous]
        public IActionResult Post([FromBody] RequestModelIn requestIn)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    var request = mapper.Map<RequestModelIn, RequestEntity>(requestIn);
                    var id = requestLogic.Add(request);
                    var addedRequest = requestLogic.GetById(id);
                    var addedRequestOut = mapper.Map<RequestEntity, RequestModelOut>(addedRequest);
                    return Created("Posted succesfully", addedRequestOut);
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
        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        public ActionResult Get(int id)
        {
            RequestEntity request;
            try
            {
                request = requestLogic.GetById(id);
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            var requestOut = mapper.Map<RequestEntity, RequestModelOut>(request);
            return this.Ok(requestOut);
        }

        [HttpPut("{id}")]
        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        public IActionResult Put(int id, [FromBody] RequestModelIn requestIn)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    requestIn.Id = id;
                    var request = mapper.Map<RequestModelIn, RequestEntity>(requestIn);
                    requestLogic.Update(request);
                    var updatedRequest = requestLogic.GetById(id);
                    var updatedRequestModelOut = mapper.Map<RequestEntity, RequestModelOut>(updatedRequest);
                    return Created("Put succesfully", updatedRequestModelOut);
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

        [AllowAnonymous]
        [HttpGet("{id}/status")]
        public IActionResult GetRequestStatus(int id)
        {
            string status;
            try
            {
                status = requestLogic.GetRequestStatus(id);
            }
            catch (ArgumentException e)
            {
                return BadRequest(e.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            return this.Ok("{\"message\": \"" + "La request de id " + id + ", tiene estado: " + status + "\"}");
        }

        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        [HttpGet("reportA/{dateFrom}/{dateTo}/{mail}")]
        public ActionResult ReportA(string dateFrom, string dateTo, string mail)
        {
            IEnumerable<string> list;
            try
            {
                list = requestLogic.ReportA(dateFrom, dateTo, mail);
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            return this.Ok(list);
        }

        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        [HttpGet("reportB/{dateFrom}/{dateTo}")]
        public ActionResult ReportB(string dateFrom, string dateTo)
        {
            IEnumerable<string> list;
            try
            {
                list = requestLogic.ReportB(dateFrom, dateTo);
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            return this.Ok(list);
        }
    }
}
