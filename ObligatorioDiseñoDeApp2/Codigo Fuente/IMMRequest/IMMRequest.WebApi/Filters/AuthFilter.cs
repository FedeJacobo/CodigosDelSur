using System;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using System.Collections.Generic;
using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess;
using IMMRequest.BusinessLogic;

namespace IMMRequest.WebApi.Filters
{
    public class AuthFilter : Attribute, IAuthorizationFilter
    {
        private readonly List<string> roles;
        private ISessionLogic sessionLogic;

        public AuthFilter(ISessionLogic sessionLogic)
        {
            this.sessionLogic = sessionLogic;
        }

        public AuthFilter(string[] roles, ISessionLogic sessionLogic)
        {
            this.sessionLogic = sessionLogic;
            this.roles = new List<string>(roles);
        }

        public void OnAuthorization(AuthorizationFilterContext context)
        {
            string token = context.HttpContext.Request.Headers["Authorization"];
            if (token == null)
            {
                context.Result = new ContentResult()
                {
                    StatusCode = 401,
                    Content = "Token required!"
                };
            }
            else
            {
                try
                {
                    Guid parsedToken = Guid.Parse(token);
                    VerifyToken(parsedToken, context);
                }
                catch (FormatException)
                {
                    context.Result = new ContentResult()
                    {
                        Content = "Invalid token format",
                    };
                }
            }
        }

        private void VerifyToken(Guid token, AuthorizationFilterContext context)
        {

            if (!this.sessionLogic.IsValidToken(token))
            {
                context.Result = new ContentResult()
                {
                    Content = "Invalid token",
                };
            }
            if (!this.sessionLogic.HasLevel(token, roles))
            {
                context.Result = new ContentResult()
                {
                    Content = "You have to be an admin to do this!",
                };
            }
        }
    }
}