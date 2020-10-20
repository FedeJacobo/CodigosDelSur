using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.WebApi.Models;
using IMMRequest.WebApi.Mapper;
using Microsoft.AspNetCore.Mvc;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System;
using System.Collections.Generic;
using IMMRequest.WebApi.Controllers;
using IMMRequest.Entities;

namespace IMMRequest.WebApi.Test
{
    [TestClass]
    public class UserControllerTest
    {
        private IWebApiMapper webApiMapper;
        private UserEntity user;
        private RequestEntity request;
        private UserModelOut userModelOut;
        private UserModelIn userModelIn;
        private Mock<IUserLogic> userLogicMock;
        private UserController userController;

        [TestInitialize]
        public void TestInitialize()
        {
            webApiMapper = new WebApiMapper();
            user = new UserEntity
            {
                Id = 1,
                CompleteName = "Nahuel Kleiman",
                Mail = "nkleiman@gmail.com",
                Password = "pass",
                Requests = new List<RequestEntity>(),
                IsAdmin = false
            };
            request = new RequestEntity
            {
                Id = 1,
                Detail = "Un contenedor roto en la esquina de Av. Italia y Bolivia",
                ApplicantName = "Nahuel Kleiman",
                Mail = "nkleiman@gmail.com",
                Phone = "098555666",
                RequestTypeEntityId = 1
            };
            userModelOut = new UserModelOut()
            {
                Id = 1,
                CompleteName = "Nahuel Kleiman",
                Mail = "nkleiman@gmail.com",
                Password = "pass",
                IsAdmin = false
            };
            userModelIn = new UserModelIn()
            {
                Id = 1,
                CompleteName = "Nahuel Kleiman",
                Mail = "nkleiman@gmail.com",
                Password = "pass",
                IsAdmin = false
            };
            userLogicMock = new Mock<IUserLogic>();
            userController = new UserController(userLogicMock.Object, webApiMapper);
        }

        [TestMethod]
        public void CreateUser_ExpectOk()
        {
            userLogicMock.Setup(userLogic => userLogic.Add(user)).Returns(user.Id);
            userLogicMock.Setup(userLogic => userLogic.GetById(user.Id)).Returns(user);

            var result = userController.Post(userModelIn);
            var createdResult = result as CreatedResult;
            var modelOut = createdResult.Value as UserModelOut;

            userLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(201, createdResult.StatusCode);
            Assert.AreEqual(userModelIn.Id, modelOut.Id);
        }

        [TestMethod]
        public void CreateUser_ExpectAlreadyExistentUserError()
        {
            userLogicMock.Setup(userLogic => userLogic.Add(user))
                .Throws(new ArgumentException("This user already exists"));

            var result = userController.Post(userModelIn);

            var createdResult = result as BadRequestObjectResult;

            userLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]

        public void GetAllUsers_ExpectOk()
        {
            ICollection<UserEntity> users = new List<UserEntity>();
            users.Add(user);
            IEnumerable<UserEntity> usersEnum = users;
            userLogicMock.Setup(method => method.GetAll()).Returns(usersEnum);

            ICollection<UserModelOut> expected = new List<UserModelOut>() { userModelOut };

            var result = userController.Get();
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as List<UserModelOut>;

            userLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Count, resultModelOut.Count);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetAllUsers_ExpectError()
        {
            userLogicMock.Setup(method => method.GetAll())
                .Throws(new ArgumentException("There are no users"));

            var result = userController.Get();
            var deletedResult = result as BadRequestObjectResult;

            userLogicMock.VerifyAll();
            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(400, deletedResult.StatusCode);
        }

        [TestMethod]
        public void GetById_UserModelIn_ExpectOk()
        {
            userLogicMock.Setup(method => method.GetById(user.Id)).Returns(user);

            var expected = userModelOut;

            var result = userController.Get(user.Id);
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as UserModelOut;

            userLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Id, resultModelOut.Id);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetById_UserModelIn_ExpectError()
        {
            userLogicMock.Setup(method => method.GetById(user.Id))
                .Throws(new ArgumentException("User not found"));

            var expected = userModelOut;

            var result = userController.Get(user.Id);
            var createdResult = result as BadRequestObjectResult;

            userLogicMock.VerifyAll();
            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void Put_Expects_BadRequest()
        {
            var modelIn = new UserModelIn();

            userController.ModelState.AddModelError("", "Error");
            var result = userController.Put(0, modelIn);

            var createdResult = result as BadRequestObjectResult;

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void Put_Expects_Ok()
        {

            UserEntity updatedUser = user;
            updatedUser.CompleteName = "new name";

            userModelIn.CompleteName = "new name";
            userLogicMock.Setup(service => service.Update(user));
            userLogicMock.Setup(service => service.GetById(user.Id)).Returns(updatedUser);


            var result = userController.Put(updatedUser.Id, userModelIn);
            var updatedResult = result as CreatedResult;
            var modelOut = updatedResult.Value as UserModelOut;

            userLogicMock.VerifyAll();

            Assert.IsNotNull(result);
            Assert.IsNotNull(updatedResult);
            Assert.AreEqual(modelOut.CompleteName, userModelIn.CompleteName);
            Assert.AreEqual(201, updatedResult.StatusCode);
        }

        [TestMethod]
        public void Put_Expects_NonExistingUser()
        {
            userLogicMock.Setup(service => service.GetById(user.Id))
                .Throws(new ArgumentException("User not found"));

            var result = userController.Put(user.Id, userModelIn);

            var createdResult = result as BadRequestObjectResult;

            userLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void Delete_Expects_Ok()
        {
            userLogicMock.Setup(service => service.Delete(user.Id));

            var result = userController.Delete(userModelIn.Id);
            var deletedResult = result as OkResult;
            userLogicMock.VerifyAll();

            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(200, deletedResult.StatusCode);
        }

        [TestMethod]
        public void Delete_Expects_NonExistingUser()
        {
            userLogicMock.Setup(service => service.Delete(user.Id))
                .Throws(new ArgumentException("User not found"));

            var result = userController.Delete(userModelIn.Id);
            var deletedResult = result as BadRequestObjectResult;

            userLogicMock.VerifyAll();
            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(400, deletedResult.StatusCode);
        }

        [TestMethod]
        public void GetRequestsFromUser_ExpectsOk()
        {
            IEnumerable<RequestEntity> requests = new List<RequestEntity>() { request };
            userLogicMock.Setup(method => method.GetRequests(user.Id)).Returns(requests);

            ICollection<UserModelOut> expected = new List<UserModelOut>() { userModelOut };

            var result = userController.GetRequests(user.Id);
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as List<RequestModelOut>;

            userLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Count, resultModelOut.Count);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetRequestsFromUser_ExpectError()
        {
            userLogicMock.Setup(method => method.GetRequests(user.Id))
                .Throws(new ArgumentException("User not found"));

            var result = userController.GetRequests(user.Id);
            var deletedResult = result as BadRequestObjectResult;

            userLogicMock.VerifyAll();
            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(400, deletedResult.StatusCode);
        }
    }
}
