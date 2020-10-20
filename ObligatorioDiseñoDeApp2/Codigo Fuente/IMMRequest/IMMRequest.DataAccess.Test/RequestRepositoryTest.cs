using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using Microsoft.EntityFrameworkCore;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Linq;

namespace IMMRequest.DataAccess.Test
{
    [TestClass]
    public class RequestRepositoryTest
    {
        private IRepository<RequestEntity> repository;
        private Context context;
        private RequestEntity requestEntity;
        private TypeReqEntity typeReqEntity;
        
        [TestInitialize]
        public void TestInitialize()
        {
            var options = new DbContextOptionsBuilder<Context>().UseInMemoryDatabase(databaseName: "TestDatabase").Options;
            context = new Context(options);
            repository = new Repository<RequestEntity>(context);
            typeReqEntity = new TypeReqEntity
            {
                Id = 1,
                Name = "Contenedor roto",
                AdditionalFields = new List<AdditionalFieldEntity>(),
                TopicEntityId = 2
            };
            requestEntity = new RequestEntity
            {
                Id = 1,
                Detail = "Contenedor de basura roto",
                ApplicantName = "Nahuel Kleiman",
                Mail = "nahuel@hotmail.com",
                Phone = "099565656",
                RequestTypeEntityId = 3,
                Status = "ACEPTADA"
            };
        }

        [TestCleanup]
        public void CleanUp()
        {
            context.Database.EnsureDeleted();
        }

        [TestMethod]
        public void GetAllTest()
        {
            repository.Add(requestEntity);
            IEnumerable<RequestEntity> result = repository.GetAll();

            Assert.IsNotNull(result);
            Assert.AreEqual(1, result.Count());
            Assert.AreEqual(requestEntity, result.First());
        }

        [TestMethod]
        public void GetTest()
        {
            repository.Add(requestEntity);
            IEnumerable<RequestEntity> result = repository.Get(u => u.Id == requestEntity.Id);
            RequestEntity firstRequest = result.First();

            Assert.IsNotNull(result);
            Assert.IsNotNull(firstRequest);
            Assert.AreEqual(1, result.Count());
            Assert.AreEqual(requestEntity, firstRequest);
        }

        [TestMethod]
        public void GetNonExistentRequestTest()
        {
            repository.Add(requestEntity);
            int idNonExist = 2;
            IEnumerable<RequestEntity> result = repository.Get(u => u.Id == idNonExist);

            Assert.AreEqual(0, result.Count());
        }

        [TestMethod]
        public void FirstOrDefaultTrueTest()
        {
            repository.Add(requestEntity);
            RequestEntity result = repository.FirstOrDefault(u => u.Id == requestEntity.Id);

            Assert.IsNotNull(result);
            Assert.AreEqual(requestEntity, result);
        }

        [TestMethod]
        public void FirstOrDefaultFalseTest()
        {
            repository.Add(requestEntity);
            var result = repository.FirstOrDefault(u => u.Id == 2);

            Assert.IsNull(result);
        }

        [TestMethod]
        public void GetRequestTypeOk()
        {
            repository.Add(requestEntity);
            var result = repository.FirstOrDefault(u => u.Id == 1);
            Assert.IsNotNull(result.RequestTypeEntityId);
        }

        [TestMethod]
        public void GetRequestStatusOk()
        {
            repository.Add(requestEntity);
            var result = repository.FirstOrDefault(u => u.Id == 1);
            Assert.IsNotNull(result.Status);
        }
    }
}
