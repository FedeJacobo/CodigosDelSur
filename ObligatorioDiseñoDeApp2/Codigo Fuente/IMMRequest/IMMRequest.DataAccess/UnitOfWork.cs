using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.DataAccess
{
    public class UnitOfWork : IUnitOfWork
    {
        private Context context;
        private IRepository<UserEntity> userRepository;
        private IRepository<RequestEntity> requestRepository;
        private IRepository<AdditionalFieldEntity> additionalFieldRepository;
        private IRepository<TypeReqEntity> typeReqRepository;
        private IRepository<SessionEntity> sessionRepository;
        private IRepository<TopicEntity> topicRepository;
        private IRepository<AreaEntity> areaRepository;
        private bool disposed = false;

        public UnitOfWork(Context context)
        {
            this.context = context;
        }

        public IRepository<UserEntity> UserRepository
        {
            get
            {
                if (userRepository == null)
                {
                    userRepository = new Repository<UserEntity>(context);
                }
                return userRepository;
            }
        }

        public IRepository<RequestEntity> RequestRepository
        {
            get
            {
                if (requestRepository == null)
                {
                    requestRepository = new Repository<RequestEntity>(context);
                }
                return requestRepository;
            }
        }

        public IRepository<AdditionalFieldEntity> AdditionalFieldRepository
        {
            get
            {
                if (additionalFieldRepository == null)
                {
                    additionalFieldRepository = new Repository<AdditionalFieldEntity>(context);
                }
                return additionalFieldRepository;
            }
        }

        public IRepository<TypeReqEntity> TypeReqRepository
        {
            get
            {
                if (typeReqRepository == null)
                {
                    typeReqRepository = new Repository<TypeReqEntity>(context);
                }
                return typeReqRepository;
            }
        }

        public IRepository<SessionEntity> SessionRepository
        {
            get
            {
                if (sessionRepository == null)
                {
                    sessionRepository = new Repository<SessionEntity>(context);
                }
                return sessionRepository;
            }
        }

        public IRepository<TopicEntity> TopicRepository
        {
            get
            {
                if (topicRepository == null)
                {
                    topicRepository = new Repository<TopicEntity>(context);
                }
                return topicRepository;
            }
        }

        public IRepository<AreaEntity> AreaRepository
        {
            get
            {
                if (areaRepository == null)
                {
                    areaRepository = new Repository<AreaEntity>(context);
                }
                return areaRepository;
            }
        }

        public void Save()
        {
            try
            {
                context.SaveChanges();
            }
            catch (DbUpdateException e)
            {
                throw new ArgumentException(e.Message);
            }
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposed)
            {
                if (disposing)
                {
                    context.Dispose();
                }
            }
            disposed = true;
        }

        public void Dispose()
        {
            Dispose(true);
        }
    }
}
