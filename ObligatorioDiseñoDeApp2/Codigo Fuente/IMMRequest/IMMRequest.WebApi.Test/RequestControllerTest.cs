using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.Entities;
using IMMRequest.WebApi.Controllers;
using IMMRequest.WebApi.Mapper;
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
    public class RequestControllerTest
    {
        private IWebApiMapper webApiMapper;
        private RequestEntity request;
        private RequestModelOut requestModelOut;
        private RequestModelIn requestModelIn;
        private Mock<IRequestLogic> requestLogicMock;
        private RequestController requestController;

        [TestInitialize]
        public void TestInitialize()
        {
            webApiMapper = new WebApiMapper();
            request = new RequestEntity
            {
                Detail = "Un contenedor roto en la esquina de Av. Italia y Bolivia",
                ApplicantName = "Federico Jacobo",
                Mail = "fedejacobo@gmail.com",
                Phone = "098555666",
                RequestTypeEntityId = 1,
                Status = RequestStatus.CREADA.ToString()
            };
            requestModelOut = new RequestModelOut()
            {
                Detail = "Un contenedor roto en la esquina de Av. Italia y Bolivia",
                ApplicantName = "Federico Jacobo",
                Mail = "fedejacobo@gmail.com",
                Phone = "098555666",
                Status = "CREADA"
            };
            requestModelIn = new RequestModelIn()
            {
                Detail = "Un contenedor roto en la esquina de Av. Italia y Bolivia",
                ApplicantName = "Federico Jacobo",
                Mail = "fedejacobo@gmail.com",
                Phone = "098555666"
            };
            requestLogicMock = new Mock<IRequestLogic>();
            requestController = new RequestController(requestLogicMock.Object, webApiMapper);
        }

        [TestMethod]
        public void CreateRequest_ExpectOk()
        {
            requestLogicMock.Setup(userLogic => userLogic.Add(request));
            requestLogicMock.Setup(userLogic => userLogic.GetById(request.Id)).Returns(request);

            var result = requestController.Post(requestModelIn);
            var createdResult = result as CreatedResult;
            var modelOut = createdResult.Value as RequestModelOut;

            requestLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(201, createdResult.StatusCode);
            Assert.AreEqual(requestModelIn.Id, modelOut.Id);
        }

        [TestMethod]
        public void CreateRequest_ExpectAlreadyExistentRequestError()
        {
            requestLogicMock.Setup(userLogic => userLogic.Add(request))
                .Throws(new ArgumentException("This user already exists"));

            var result = requestController.Post(requestModelIn);

            var createdResult = result as BadRequestObjectResult;

            requestLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]

        public void GetAllRequests_ExpectOk()
        {
            ICollection<RequestEntity> requests = new List<RequestEntity>();
            requests.Add(request);
            IEnumerable<RequestEntity> requestEnum = requests;
            requestLogicMock.Setup(method => method.GetAll()).Returns(requestEnum);

            ICollection<RequestModelOut> expected = new List<RequestModelOut>() { requestModelOut };

            var result = requestController.Get();
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as List<RequestModelOut>;

            requestLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Count, resultModelOut.Count);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetAllRequests_ExpectError()
        {
            requestLogicMock.Setup(method => method.GetAll())
                .Throws(new ArgumentException("There are no requests"));

            var result = requestController.Get();
            var deletedResult = result as BadRequestObjectResult;

            requestLogicMock.VerifyAll();
            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(400, deletedResult.StatusCode);
        }

        [TestMethod]
        public void GetById_RequestModelIn_ExpectOk()
        {
            requestLogicMock.Setup(method => method.GetById(request.Id)).Returns(request);

            var expected = requestModelOut;

            var result = requestController.Get(request.Id);
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as RequestModelOut;

            requestLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Id, resultModelOut.Id);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetById_RequestModelIn_ExpectError()
        {
            requestLogicMock.Setup(method => method.GetById(request.Id))
                .Throws(new ArgumentException("Request not found"));

            var expected = requestModelOut;

            var result = requestController.Get(request.Id);
            var createdResult = result as BadRequestObjectResult;

            requestLogicMock.VerifyAll();
            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void Put_Expects_BadRequest()
        {
            var modelIn = new RequestModelIn();

            requestController.ModelState.AddModelError("", "Error");
            var result = requestController.Put(0, modelIn);

            var createdResult = result as BadRequestObjectResult;

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void Put_Expects_Ok()
        {

            RequestEntity updatedRequest = request;
            updatedRequest.Detail = "new detail";

            requestModelIn.Detail = "new detail";
            requestLogicMock.Setup(service => service.Update(request));
            requestLogicMock.Setup(service => service.GetById(request.Id)).Returns(updatedRequest);


            var result = requestController.Put(updatedRequest.Id, requestModelIn);
            var updatedResult = result as CreatedResult;
            var modelOut = updatedResult.Value as RequestModelOut;

            requestLogicMock.VerifyAll();

            Assert.IsNotNull(result);
            Assert.IsNotNull(updatedResult);
            Assert.AreEqual(modelOut.Detail, requestModelIn.Detail);
            Assert.AreEqual(201, updatedResult.StatusCode);
        }

        [TestMethod]
        public void Put_Expects_NonExistingRequest()
        {
            requestLogicMock.Setup(service => service.GetById(request.Id))
                .Throws(new ArgumentException("Request not found"));

            var result = requestController.Put(request.Id, requestModelIn);

            var createdResult = result as BadRequestObjectResult;

            requestLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetRequestStatus_ExpectOk()
        {
            requestLogicMock.Setup(method => method.GetRequestStatus(request.Id)).Returns(request.Status.ToString());

            var expected = request.Status;

            var result = requestController.GetRequestStatus(request.Id);
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as string;

            requestLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetRequestStatus_ExpectError()
        {
            requestLogicMock.Setup(method => method.GetRequestStatus(request.Id))
                .Throws(new ArgumentException("Request not found"));

            var result = requestController.GetRequestStatus(request.Id);
            var createdResult = result as BadRequestObjectResult;

            requestLogicMock.VerifyAll();
            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]

        public void ReportATest()
        {
            var res = new List<string>() { "Creada (1) = [0]" };
            requestLogicMock.Setup(method => method.ReportA("24-05-2020 18:00", "26-05-2020 19:10", "pepe@hotmail.com")).Returns(res);

            var expected = new List<string>() { "Creada (1) = [0]" };

            var result = requestController.ReportA("24-05-2020 18:00", "26-05-2020 19:10", "pepe@hotmail.com");
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as List<string>;

            requestLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Count, resultModelOut.Count);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]

        public void ReportBTest()
        {
            var res = new List<string>() { "Contenedor roto (1)" };
            requestLogicMock.Setup(method => method.ReportB("24-05-2020 18:00", "26-05-2020 19:10")).Returns(res);

            var expected = new List<string>() { "Contenedor roto (1)" };

            var result = requestController.ReportB("24-05-2020 18:00", "26-05-2020 19:10");
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as List<string>;

            requestLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Count, resultModelOut.Count);
            Assert.AreEqual(200, createdResult.StatusCode);
        }
    }
}
