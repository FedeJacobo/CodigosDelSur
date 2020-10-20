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
    public class UserController : ControllerBase
    {
        private IUserLogic userLogic;
        private IMapper mapper;

        public UserController(IUserLogic userLogic, IWebApiMapper apiMapper)
        {
            this.mapper = apiMapper.Configure();
            this.userLogic = userLogic;
        }

        [AllowAnonymous]
        [HttpGet]
        public ActionResult Get()
        {
            IEnumerable<UserEntity> users;
            try
            {
                users = userLogic.GetAll();
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            var usersOut = mapper.Map<IEnumerable<UserEntity>, IEnumerable<UserModelOut>>(users);
            return this.Ok(usersOut);
        }

        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        [HttpPost]
        public IActionResult Post([FromBody] UserModelIn userIn)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    var user = mapper.Map<UserModelIn, UserEntity>(userIn);
                    var id = userLogic.Add(user);
                    var addedUser = userLogic.GetById(id);
                    var addedUserOut = mapper.Map<UserEntity, UserModelOut>(addedUser);
                    return Created("Posted succesfully", addedUserOut);
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

        [AllowAnonymous]
        [HttpGet("{id}")]
        public ActionResult Get(int id)
        {
            UserEntity user;
            try
            {
                user = userLogic.GetById(id);
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            var userOut = mapper.Map<UserEntity, UserModelOut>(user);
            return this.Ok(userOut);
        }

        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        [HttpPut("{id}")]
        public IActionResult Put(int id, [FromBody] UserModelIn userIn)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    userIn.Id = id;
                    var user = mapper.Map<UserModelIn, UserEntity>(userIn);
                    userLogic.Update(user);
                    var updatedUser = userLogic.GetById(id);
                    var updatedUserModelOut = mapper.Map<UserEntity, UserModelOut>(updatedUser);
                    return Created("Put succesfully", updatedUserModelOut);
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

        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        [HttpDelete("{id}")]
        public IActionResult Delete(int id)
        {
            try
            {
                userLogic.Delete(id);
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
        [HttpGet("{id}/request")]
        public ActionResult GetRequests(int id)
        {
            IEnumerable<RequestEntity> requests;
            try
            {
                requests = userLogic.GetRequests(id);
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
    }
}
