using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Linq.Expressions;
using System.Text;

namespace IMMRequest.BusinessLogic.Interfaces
{
    public interface IUserLogic
    {
        int Add(UserEntity user);
        IEnumerable<UserEntity> GetAll();
        UserEntity GetById(int id);
        UserEntity GetByName(string name);
        UserEntity GetByMail(string mail);
        void Delete(int id);
        void Update(UserEntity user);
        IEnumerable<RequestEntity> GetRequests(int userId);
    }
}
