using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.BusinessLogic
{
    public class SessionLogic : ISessionLogic
    {
        private IRepository<SessionEntity> sessionRepository;
        private IUnitOfWork unitOfWork;
        public SessionLogic(IUnitOfWork unitOfWork)
        {
            this.unitOfWork = unitOfWork;
            this.sessionRepository = unitOfWork.SessionRepository;
        }
        public void Dispose()
        {
            unitOfWork.Dispose();

        }

        public bool IsValidToken(Guid token)
        {
            try
            {
                SessionEntity sessionEntity = sessionRepository.FirstOrDefault(s => s.Token == token);
                return sessionEntity != null;
            }
            catch (ArgumentException)
            {
                return false;
            }
        }

        public Guid Login(string mail, string password)
        {
            try
            {
                Guid sessionToken = Guid.NewGuid();
                UserEntity adminEntity = unitOfWork.UserRepository.FirstOrDefault(u => u.Mail.Equals(mail) && u.Password.Equals(password));
                if (adminEntity != null)
                {
                    if (adminEntity.IsAdmin)
                    {
                        SessionEntity session = new SessionEntity()
                        {
                            Token = sessionToken,
                            Mail = adminEntity.Mail,
                            AdminId = adminEntity.Id
                        };
                        sessionRepository.Add(session);
                        unitOfWork.Save();
                        return sessionToken;
                    }
                    else
                    {
                        throw new ArgumentException("You have to be an admin to login");
                    }
                }
                else
                {
                    throw new ArgumentException("Username/Password not valid");
                }
            }
            catch (InvalidOperationException)
            {
                throw new ArgumentException("Username/Password not valid");
            }
        }

        public void Logout(int adminId)
        {
            try
            {
                ValidateSession(adminId);
                var userEntity = unitOfWork.UserRepository.FirstOrDefault(u => u.Id == adminId);
                var sessionToken = sessionRepository.FirstOrDefault(x => x.Mail.Equals(userEntity.Mail));
                sessionRepository.Delete(sessionToken);
                unitOfWork.Save();
            }
            catch (InvalidOperationException)
            {
                throw new ArgumentException($"Admin with id: {adminId} is not logged into the system");
            }
        }

        private void ValidateSession(int id)
        {
            if (!sessionRepository.Exists(s => s.AdminId.Equals(id)))
            {
                throw new ArgumentException($"Admin with id: {id} is not logged into the system");
            }
        }

        public bool HasLevel(Guid token, List<string> roles)
        {
            try
            {
                SessionEntity sessionForToken = sessionRepository.FirstOrDefault(s => s.Token == token);

                return unitOfWork.UserRepository.Exists(u => u.Mail == sessionForToken.Mail && u.IsAdmin);
            }
            catch (Exception)
            {
                return false;
            }
        }
    }
}