using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Linq;

namespace IMMRequest.BusinessLogic
{
    public class UserLogic : IUserLogic
    {
        private readonly IUnitOfWork unitOfWork;

        public UserLogic(IUnitOfWork unitOfWork)
        {
            this.unitOfWork = unitOfWork;
        }

        public int Add(UserEntity user)
        {
            ValidateUserIdExistance(user.Id);
            ValidateUserMailExistance(user.Mail);
            unitOfWork.UserRepository.Add(user);
            unitOfWork.Save();
            return unitOfWork.UserRepository.FirstOrDefault(u => u.Id == user.Id).Id;
        }

        private void ValidateUserMailExistance(string mail)
        {
            if (UserMailExist(mail))
                throw new ArgumentException("This mail is taken, please try another one");
        }

        private void ValidateUserIdExistance(int id)
        {
            if (UserExist(id))
                throw new ArgumentException("This user already exist");
        }

        private bool UserMailExist(string mail)
        {
            return unitOfWork.UserRepository.Exists(u => !u.IsDeleted && u.Mail == mail);
        }

        private bool UserExist(int id)
        {
            return unitOfWork.UserRepository.Exists(u => !u.IsDeleted && u.Id == id);
        }

        public void Delete(int id)
        {
            if (!UserExist(id))
                throw new ArgumentException($"User with id: {id} doesn't exist");
            UserEntity userEntity = unitOfWork.UserRepository.FirstOrDefault(u => u.Id == id && !u.IsDeleted);
            userEntity.IsDeleted = true;
            unitOfWork.UserRepository.Update(userEntity);
            unitOfWork.Save();
        }

        public UserEntity GetById(int id)
        {
            if (!UserExist(id))
                throw new ArgumentException($"User with id: {id} doesn't exist");
            UserEntity ret = unitOfWork.UserRepository.FirstOrDefault(u => u.Id == id && !u.IsDeleted);
            return ret;
        }

        public UserEntity GetByMail(string mail)
        {
            if(!UserMailExist(mail)) throw new ArgumentException($"User with mail: {mail} doesn't exist");
            UserEntity ret = unitOfWork.UserRepository.FirstOrDefault(u => u.Mail == mail && !u.IsDeleted);
            return ret;
        }

        public UserEntity GetByName(string name)
        {
            ValidateUserNameExistance(name);
            UserEntity ret = unitOfWork.UserRepository.FirstOrDefault(u => u.CompleteName == name && !u.IsDeleted);
            return ret;
        }

        private void ValidateUserNameExistance(string name)
        {
            if (!UserNameExist(name))
                throw new ArgumentException($"User with name: {name} doesn't exist");
        }

        private bool UserNameExist(string name)
        {
            return unitOfWork.UserRepository.Exists(u => !u.IsDeleted && u.CompleteName == name);
        }

        public IEnumerable<UserEntity> GetAll()
        {
            IEnumerable<UserEntity> userEntitiesResult = unitOfWork.UserRepository.GetAll().Where(x => !x.IsDeleted).ToList();
            return userEntitiesResult;
        }

        public void Update(UserEntity user)
        {
            if (!UserExist(user.Id))
                throw new ArgumentException($"User with id: {user.Id} doesn't exist");
            UserEntity userToUpdate = unitOfWork.UserRepository.FirstOrDefault(u => u.Id == user.Id && !user.IsDeleted);
            userToUpdate.CompleteName = user.CompleteName;
            userToUpdate.Password = user.Password;
            CheckIfRequestsAreNull(user);
            unitOfWork.UserRepository.Update(userToUpdate);
            unitOfWork.Save();
        }

        private static void CheckIfRequestsAreNull(UserEntity user)
        {
            if (user.Requests == null)
            {
                user.Requests = new List<RequestEntity>();
            }
        }

        public IEnumerable<RequestEntity> GetRequests(int userId)
        {
            if (!UserExist(userId))
                throw new ArgumentException($"User with id: {userId} doesn't exist");
            List<RequestEntity> result = new List<RequestEntity>();
            IEnumerable<RequestEntity> requestsEntities = unitOfWork.RequestRepository.GetAll();
            foreach (var entity in requestsEntities)
            {
                UserEntity userEntity = unitOfWork.UserRepository.FirstOrDefault(u => u.Mail.Equals(entity.Mail));
                if (userEntity != null && userId == userEntity.Id)
                {
                    result.Add(entity);
                }
            }
            return result;
        }
    }
}
