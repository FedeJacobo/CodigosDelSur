using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using Microsoft.EntityFrameworkCore;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Linq;

namespace IMMRequest.DataAccess.Test
{
    [TestClass]
    public class UserRepositoryTest
    {
        private IRepository<UserEntity> repository;
        private Context context;
        private UserEntity userEntity;

        [TestInitialize]
        public void TestInitialize()
        {
            var options = new DbContextOptionsBuilder<Context>().UseInMemoryDatabase(databaseName: "TestDatabase").Options;
            context = new Context(options);
            repository = new Repository<UserEntity>(context);
            userEntity = new UserEntity();
            userEntity.CompleteName = "Federico Jacobo";
            userEntity.Id = 1;
        }

        [TestCleanup]
        public void CleanUp()
        {
            context.Database.EnsureDeleted();
        }

        [TestMethod]
        public void GetAllTest()
        {
            repository.Add(userEntity);
            IEnumerable<UserEntity> result = repository.GetAll();

            Assert.IsNotNull(result);
            Assert.AreEqual(1, result.Count());
            Assert.AreEqual(userEntity, result.First());
        }

        [TestMethod]
        public void GetTest()
        {
            repository.Add(userEntity);
            IEnumerable<UserEntity> result = repository.Get(u => u.Id == userEntity.Id);
            UserEntity firstUser = result.First();

            Assert.IsNotNull(result);
            Assert.IsNotNull(firstUser);
            Assert.AreEqual(1, result.Count());
            Assert.AreEqual(userEntity, firstUser);
        }

        [TestMethod]
        public void GetNonExistentUserTest()
        {
            repository.Add(userEntity);
            int idNonExist = 2;
            IEnumerable<UserEntity> result = repository.Get(u => u.Id == idNonExist);

            Assert.AreEqual(0, result.Count());
        }

        [TestMethod]
        public void FirstOrDefaultTrueTest()
        {
            repository.Add(userEntity);
            UserEntity result = repository.FirstOrDefault(u => u.Id == userEntity.Id);

            Assert.IsNotNull(result);
            Assert.AreEqual(userEntity, result);
        }

        [TestMethod]
        public void FirstOrDefaultFalseTest()
        {
            repository.Add(userEntity);
            var result = repository.FirstOrDefault(u => u.Id == 2);

            Assert.IsNull(result);
        }

        [TestMethod]
        public void GetUserRequestsOk()
        {
            RequestEntity req = new RequestEntity();
            req.Id = 3;
            UserEntity toAdd = new UserEntity();
            toAdd.Id = 1;
            toAdd.Requests = new RequestEntity[] { req };
            repository.Add(toAdd);
            var result = repository.Get(u => u.Id == toAdd.Id);

            Assert.IsNotNull(result);
            Assert.AreEqual(toAdd.Requests, result.First().Requests);
        }
    }
}
