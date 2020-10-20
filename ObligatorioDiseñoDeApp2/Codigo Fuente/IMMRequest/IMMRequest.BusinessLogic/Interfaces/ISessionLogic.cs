using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.BusinessLogic.Interfaces
{
    public interface ISessionLogic : IDisposable
    {
        Guid Login(string mail, string password);
        void Logout(int adminId);
        bool IsValidToken(Guid token);
        bool HasLevel(Guid token, List<string> roles);
    }
}
