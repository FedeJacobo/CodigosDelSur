using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.DataAccess.Interfaces
{
    public interface IUnitOfWork : IDisposable
    {
        IRepository<UserEntity> UserRepository { get; }

        IRepository<RequestEntity> RequestRepository { get; }

        IRepository<AdditionalFieldEntity> AdditionalFieldRepository { get; }

        IRepository<TypeReqEntity> TypeReqRepository { get; }

        IRepository<SessionEntity> SessionRepository { get; }

        IRepository<TopicEntity> TopicRepository { get; }
        IRepository<AreaEntity> AreaRepository { get; }

        void Save();
    }
}
