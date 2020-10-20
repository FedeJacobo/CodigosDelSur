using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;

namespace IMMRequest.BusinessLogic.Test
{
    [TestClass]
    public class UserLogicTest
    {
        protected Mock<IRepository<UserEntity>> userRepository;
        protected Mock<IRepository<RequestEntity>> requestRepository;
        protected Mock<IUnitOfWork> unitOfWork;
        private IUserLogic userLogic;
        private UserEntity testUserEntity;
        private RequestEntity testRequestEntity;

        [TestInitialize]
        public void TestInitialize()
        {
            testUserEntity = new UserEntity
            {
                Id = 1234,
                CompleteName = "Federico Jacobo",
                Mail = "fjacobo@gmail.com",
                Password = "password",
                Requests = new List<RequestEntity>()
            };

            testRequestEntity = new RequestEntity
            {
                Detail = "Un contenedor roto en la esquina de Av. Italia y Bolivia",
                ApplicantName = "Federico Jacobo",
                Mail = "fjacobo@gmail.com",
                Phone = "098555666",
                RequestTypeEntityId = 1,
                Status = "CREADA"
            };

            userRepository = new Mock<IRepository<UserEntity>>(MockBehavior.Strict);
            requestRepository = new Mock<IRepository<RequestEntity>>(MockBehavior.Strict);
            unitOfWork = new Mock<IUnitOfWork>();
            unitOfWork.Setup(u => u.UserRepository).Returns(userRepository.Object);
            unitOfWork.Setup(r => r.RequestRepository).Returns(requestRepository.Object);
            userLogic = new UserLogic(unitOfWork.Object);
        }

        [TestMethod]
        public void AddNewUserTest()
        {
            userRepository.SetupSequence(r => r.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>()))
                .Returns(false).Returns(false).Returns(true).Returns(true);
            userRepository.Setup(u => u.Add(It.IsAny<UserEntity>())).Verifiable();
            userRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntity);
            unitOfWork.Setup(r => r.Save());
            userRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntity);

            var result = userLogic.Add(testUserEntity);
            UserEntity userResult = unitOfWork.Object.UserRepository.FirstOrDefault(u => u.Id == result);

            userRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testUserEntity.Id, userResult.Id);
            Assert.AreEqual(testUserEntity.CompleteName, userResult.CompleteName);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void AddNewUserInvalidTest()
        {
            userRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(true);

            userLogic.Add(testUserEntity);

            userRepository.VerifyAll();
        }

        [TestMethod]
        public void GetAllUsersTest()
        {
            var users = new List<UserEntity>() { testUserEntity };
            userRepository.Setup(x => x.GetAll()).Returns(users);

            var result = userLogic.GetAll();

            userRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(1, result.Count());
            Assert.AreEqual(result.FirstOrDefault(), testUserEntity);
        }

        [TestMethod]
        public void GetByIdTestOk()
        {
            userRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(true);
            userRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntity);

            var result = userLogic.GetById(testUserEntity.Id);

            userRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testUserEntity.CompleteName, result.CompleteName);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetByIdNotFoundTest()
        {
            userRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(false);
            userLogic.GetById(testUserEntity.Id);

            userRepository.VerifyAll();
        }

        [TestMethod]
        public void GetByNameTestOk()
        {
            userRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(true);
            userRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntity);

            var result = userLogic.GetByName(testUserEntity.CompleteName);

            userRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testUserEntity.Mail, result.Mail);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetByNameNotFoundTest()
        {
            userRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(false);
            userLogic.GetByMail(testUserEntity.Mail);

            userRepository.VerifyAll();
        }

        [TestMethod]
        public void GetByMailTestOk()
        {
            userRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(true);
            userRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntity);

            var result = userLogic.GetByMail(testUserEntity.Mail);

            userRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testUserEntity.Mail, result.Mail);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetByMailNotFoundTest()
        {
            userRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(false);
            userLogic.GetByName(testUserEntity.CompleteName);

            userRepository.VerifyAll();
        }

        [TestMethod]
        public void DeleteUserTest()
        {
            userRepository.SetupSequence(r => r.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(true);
            userRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntity);
            userRepository.Setup(r => r.Update(It.IsAny<UserEntity>())).Verifiable();
            unitOfWork.Setup(r => r.Save());

            userLogic.Delete(testUserEntity.Id);

            userRepository.VerifyAll();
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void DeleteUserNotFoundTest()
        {
            userRepository.Setup(r => r.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(false);
            userLogic.Delete(testUserEntity.Id);
            userRepository.VerifyAll();
        }

        [TestMethod]
        public void UpdateUserTest()
        {
            var testUserEntityUpd = new UserEntity()
            {
                Id = 1234,
                CompleteName = "Fede",
                Mail = "fj@gmail.com",
                Password = "pas",
                Requests = new List<RequestEntity>()
            };

            userRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(true);
            userRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntityUpd);
            userRepository.Setup(u => u.Update(It.IsAny<UserEntity>())).Verifiable();
            userRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntityUpd);
            unitOfWork.Setup(r => r.Save());

            userLogic.Update(testUserEntityUpd);

            var result = userLogic.GetById(testUserEntity.Id);

            userRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testUserEntityUpd.CompleteName, result.CompleteName);
        }

        [TestMethod]
        public void UpdateUserWithNullRequestListTest()
        {

            var testUserEntityUpd = new UserEntity()
            {
                Id = 1234,
                CompleteName = "Fede",
                Mail = "fj@gmail.com",
                Password = "pas"
            };

            userRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(true);
            userRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntityUpd);
            userRepository.Setup(u => u.Update(It.IsAny<UserEntity>())).Verifiable();
            userRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntityUpd);
            unitOfWork.Setup(r => r.Save());

            userLogic.Update(testUserEntityUpd);

            var result = userLogic.GetById(testUserEntity.Id);

            userRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testUserEntityUpd.CompleteName, result.CompleteName);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void UpdateUserInvalidTest()
        {
            userRepository.SetupSequence(u => u.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(false);

            userLogic.Update(testUserEntity);

            userRepository.VerifyAll();

        }

        [TestMethod]
        public void GetRequestFromUserTest()
        {
            testUserEntity.Requests.Add(testRequestEntity);
            testUserEntity.Requests.Add(testRequestEntity);
            userRepository.Setup(w => w.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(true);
            requestRepository.Setup(w => w.GetAll()).Returns(testUserEntity.Requests);
            userRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntity);

            var result = userLogic.GetRequests(testUserEntity.Id);

            userRepository.VerifyAll();
            Assert.IsNotNull(result);
        }
    }
}
