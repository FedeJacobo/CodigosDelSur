using System;
using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.Entities;
using IMMRequest.WebApi.Filters;
using IMMRequest.WebApi.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace IMMRequest.WebApi.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class SessionController : ControllerBase, IDisposable
    {
        private ISessionLogic sessionLogic;
        private IUserLogic userLogic;

        public SessionController(ISessionLogic sessionLogic, IUserLogic userLogic)
        {
            this.sessionLogic = sessionLogic;
            this.userLogic = userLogic;
        }

        [AllowAnonymous]
        [HttpPost("login")]
        public IActionResult Login([FromBody] LoginModelIn login)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    Guid token = sessionLogic.Login(login.Mail, login.Password);
                    if (token == null)
                    {
                        return BadRequest("You have entered a wrong mail or password. Try again!");
                    }
                    UserEntity admin = userLogic.GetByMail(login.Mail);
                    return Ok(new LoginModelOut
                    {
                        Token = token,
                        Mail = admin.Mail,
                        IsAdmin = admin.IsAdmin
                    });
                }
                catch (ArgumentException e)
                {
                    return Unauthorized(e.Message);
                }
                catch (Exception ex)
                {
                    return BadRequest(ex.Message);
                }
            }
            else
            {
                return Unauthorized(ModelState);
            }
        }

        [TypeFilter(typeof(AuthFilter), Arguments = new object[] { new string[] { "Admin" } })]
        [HttpDelete("logout/{id}")]
        public IActionResult Logout(int id)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    sessionLogic.Logout(id);
                    return Ok();
                }
                catch (ArgumentException e)
                {
                    return BadRequest(e.Message);
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

        public void Dispose()
        {
            sessionLogic.Dispose();
        }
    }
}