using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.Entities;
using IMMRequest.WebApi.Controllers;
using IMMRequest.WebApi.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.WebApi.Test
{
    [TestClass]
    public class SessionControllerTest
    {
        private Mock<ISessionLogic> sessionLogicMock;
        private Mock<IUserLogic> userLogicMock;
        private SessionController sessionController;
        private UserEntity testUser;
        private LoginModelIn login;

        [TestInitialize]
        public void TestInitialize()
        {
            testUser = new UserEntity
            {
                Id = 1,
                CompleteName = "Juan Perez",
                Mail = "mail@mail.com",
                Password = "pass",
                Requests = new List<RequestEntity>(),
                IsAdmin = false
            };

            login = new LoginModelIn
            {
                Mail = "mail@mail.com",
                Password = "pass"
            };

            sessionLogicMock = new Mock<ISessionLogic>();
            userLogicMock = new Mock<IUserLogic>();
            sessionController = new SessionController(sessionLogicMock.Object, userLogicMock.Object);
        }

        [TestMethod]
        public void Login_ExpectOk()
        {
            sessionLogicMock.Setup(sessionLogic => sessionLogic.Login(testUser.Mail, testUser.Password)).Returns(new Guid());
            userLogicMock.Setup(userLogic => userLogic.GetByMail(testUser.Mail)).Returns(testUser);

            var result = sessionController.Login(login);
            var createdResult = result as OkObjectResult;
            var modelOut = createdResult.Value as LoginModelOut;

            sessionLogicMock.VerifyAll();
            userLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void Login_ExpectBadRequest()
        {
            sessionLogicMock.Setup(sessionLogic => sessionLogic.Login(testUser.Mail, testUser.Password))
                .Throws(new ArgumentException("Username/Password not valid"));

            var result = sessionController.Login(login);
            var createdResult = result as UnauthorizedObjectResult;

            sessionLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(401, createdResult.StatusCode);
        }
        [TestMethod]
        public void Logout_ExpectOk()
        {
            sessionLogicMock.Setup(sessionLogic => sessionLogic.Logout(testUser.Id)).Verifiable();

            var result = sessionController.Logout(testUser.Id);
            var createdResult = result as OkResult;

            sessionLogicMock.VerifyAll();
            userLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void Logout_ExpectBadRequest()
        {
            sessionLogicMock.Setup(sessionLogic => sessionLogic.Logout(testUser.Id))
                .Throws(new ArgumentException("Admin with id: "+ testUser.Id +" is not logged into the system"));

            var result = sessionController.Logout(testUser.Id);
            var createdResult = result as BadRequestObjectResult;

            sessionLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void Dispose_ExpectOk()
        {
            sessionLogicMock.Setup(sessionLogic => sessionLogic.Dispose()).Verifiable();

            sessionController.Dispose();
            sessionLogicMock.VerifyAll();
        }
    }
}
