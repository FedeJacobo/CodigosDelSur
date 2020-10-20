using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System;
using System.Collections.Generic;
using System.Linq.Expressions;

namespace IMMRequest.BusinessLogic.Test
{
    [TestClass]
    public class SessionLogicTest
    {
        protected UserEntity adminEntity;
        protected Mock<IRepository<UserEntity>> userRepository;
        protected Mock<IRepository<SessionEntity>> sessionRepository;
        protected Mock<IUnitOfWork> unitOfWork;
        protected ISessionLogic sessionLogic;
        protected SessionEntity testSessionEntity;

        [TestInitialize]
        public void TestInitialize()
        {
            adminEntity = new UserEntity
            {
                Id = 1,
                CompleteName = "Nahuel Kleiman",
                Mail = "nahuel@gmail.com",
                Password = "pass",
                Requests = new List<RequestEntity>(),
                IsAdmin = true
            };

            testSessionEntity = new SessionEntity
            {
                AdminId = 1,
                Id = new Guid(),
                Mail = "mail@mail.com",
                Token = new Guid()
            };

            userRepository = new Mock<IRepository<UserEntity>>(MockBehavior.Strict);
            sessionRepository = new Mock<IRepository<SessionEntity>>(MockBehavior.Strict);
            unitOfWork = new Mock<IUnitOfWork>();
            unitOfWork.Setup(x => x.SessionRepository).Returns(sessionRepository.Object);
            sessionLogic = new SessionLogic(unitOfWork.Object);
        }

        [TestMethod]
        public void Login_ExpectsOk()
        {
            unitOfWork.Setup(x => x.UserRepository.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(adminEntity);
            sessionRepository.Setup(u => u.Add(It.IsAny<SessionEntity>())).Verifiable();

            var guid = sessionLogic.Login(adminEntity.Mail, adminEntity.Password);

            SessionEntity sessionEntity = new SessionEntity { Token = guid, Mail = adminEntity.Mail };
            sessionRepository.Setup(x => x.FirstOrDefault(It.IsAny<Expression<Func<SessionEntity, bool>>>())).Returns(sessionEntity);

            var isValid = sessionLogic.IsValidToken(guid);

            sessionRepository.VerifyAll();
            Assert.IsTrue(isValid);
        }

        [TestMethod]
        public void Logout_ExpectsOk()
        {
            sessionRepository.Setup(x => x.Exists(It.IsAny<Expression<Func<SessionEntity, bool>>>())).Returns(true);
            unitOfWork.Setup(x => x.UserRepository.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(adminEntity);
            sessionRepository.Setup(u => u.Add(It.IsAny<SessionEntity>())).Verifiable();
            var guid = sessionLogic.Login(adminEntity.Mail, adminEntity.Password);

            SessionEntity sessionEntity = new SessionEntity { Token = guid, Mail = adminEntity.Mail };
            sessionRepository.Setup(x => x.FirstOrDefault(It.IsAny<Expression<Func<SessionEntity, bool>>>())).Returns(sessionEntity);
            sessionRepository.Setup(u => u.Delete(It.IsAny<SessionEntity>())).Verifiable();

            sessionLogic.Logout(adminEntity.Id);

            sessionRepository.VerifyAll();
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void Logout_ExpectsError()
        {
            sessionRepository.Setup(x => x.Exists(It.IsAny<Expression<Func<SessionEntity, bool>>>())).Returns(true);
            unitOfWork.Setup(x => x.UserRepository.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(adminEntity);
            sessionRepository.Setup(u => u.Add(It.IsAny<SessionEntity>())).Verifiable();
            var guid = sessionLogic.Login(adminEntity.Mail, adminEntity.Password);

            SessionEntity sessionEntity = new SessionEntity { Token = guid, Mail = adminEntity.Mail };
            sessionRepository.Setup(x => x.FirstOrDefault(It.IsAny<Expression<Func<SessionEntity, bool>>>())).Returns(sessionEntity);
            sessionRepository.Setup(u => u.Delete(It.IsAny<SessionEntity>())).Verifiable();

            sessionLogic.Logout(adminEntity.Id);

            sessionRepository.Setup(x => x.FirstOrDefault(It.IsAny<Expression<Func<SessionEntity, bool>>>())).Throws(new InvalidOperationException());

            sessionLogic.Logout(adminEntity.Id);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void Login_ExpectsError()
        {
            unitOfWork.Setup(x => x.UserRepository.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Throws(new InvalidOperationException());

            var guid = sessionLogic.Login(adminEntity.Mail, adminEntity.Password);
        }

        [TestMethod]
        public void IsValidToken_ExpectsOk()
        {
            Guid guid = new Guid();
            SessionEntity sessionEntity = new SessionEntity { Token = guid, Mail = adminEntity.Mail };
            sessionRepository.Setup(x => x.FirstOrDefault(It.IsAny<Expression<Func<SessionEntity, bool>>>())).Returns(sessionEntity);

            var result = sessionLogic.IsValidToken(guid);

            sessionRepository.VerifyAll();
            Assert.IsTrue(result);
        }

        [TestMethod]
        [ExpectedException(typeof(InvalidOperationException))]
        public void IsValidToken_ExpectsError()
        {
            Guid guid = new Guid();
            SessionEntity sessionEntity = new SessionEntity { Token = guid, Mail = adminEntity.Mail };
            sessionRepository.Setup(x => x.FirstOrDefault(It.IsAny<Expression<Func<SessionEntity, bool>>>())).Throws(new InvalidOperationException());

            var result = sessionLogic.IsValidToken(guid);

            sessionRepository.VerifyAll();
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void Dispose_ExpectsOk()
        {
            unitOfWork.Setup(u => u.Dispose()).Verifiable();

            sessionLogic.Dispose();

            unitOfWork.VerifyAll();
        }

        [TestMethod]
        public void HasLevel_ExpectsOk()
        {
            sessionRepository.Setup(x => x.FirstOrDefault(It.IsAny<Expression<Func<SessionEntity, bool>>>())).Returns(testSessionEntity);
            userRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(true);

            sessionLogic.HasLevel(testSessionEntity.Token, new List<string>() { "admin" });

            unitOfWork.VerifyAll();
        }
    }
}
