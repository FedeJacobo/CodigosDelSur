using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using Microsoft.EntityFrameworkCore;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Linq;

namespace IMMRequest.DataAccess.Test
{
    [TestClass]
    public class RepositoryTest
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
            userEntity.CompleteName = "Nahuel Kleiman";
            userEntity.Id = 1;
        }

        [TestCleanup]
        public void CleanUp()
        {
            context.Database.EnsureDeleted();
        }

        [TestMethod]
        public void AddTest()
        {
            repository.Add(userEntity);
            Assert.AreEqual(1, repository.GetAll().Count());
        }


        [TestMethod]
        public void When_Delete_ExpectOk()
        {
            repository.Add(userEntity);
            repository.Delete(userEntity);
            Assert.AreEqual(0, repository.GetAll().Count());
        }


        [TestMethod]
        public void When_Update_ExpectOk()
        {
            var name = "Nahuel Kleiman";
            var newName = "Federico Jacobo";
            userEntity.CompleteName = name;
            repository.Add(userEntity);

            userEntity.CompleteName = newName;
            repository.Update(userEntity);
            var updated = repository.FirstOrDefault(u => u.Id == userEntity.Id);

            Assert.AreEqual(newName, updated.CompleteName);
        }

        [TestMethod]
        public void When_Exists_ExpectFound()
        {
            repository.Add(userEntity);
            var result = repository.Exists(u => u.Id == userEntity.Id);
            Assert.AreEqual(true, result);
        }

        [TestMethod]
        public void When_Exists_ExpectNotFount()
        {
            var result = repository.Exists(u => u.Id == userEntity.Id);
            Assert.AreEqual(false, result);
        }

        [TestMethod]
        public void When_GetAll_ExpectOk()
        {
            repository.Add(userEntity);
            var result = repository.GetAll();
            Assert.AreEqual(1, result.Count());
        }

        [TestMethod]
        public void When_Get_ExpectOk()
        {
            repository.Add(userEntity);

            var result = repository.Get(u => u.Id == userEntity.Id);

            Assert.IsNotNull(result);
            Assert.AreEqual(1, result.Count());
        }
        [TestMethod]

        public void When_GetNonExistentUser_ExpectOk()
        {
            repository.Add(userEntity);
            int nonExistentId = 5;
            IEnumerable<UserEntity> result = repository.Get(u => u.Id == nonExistentId);

            Assert.AreEqual(0, result.Count());
        }

        [TestMethod]
        public void When_FirstOrDefault_Expect_True()
        {
            repository.Add(userEntity);

            var result = repository.FirstOrDefault(u => u.Id == userEntity.Id);

            Assert.IsNotNull(result);
            Assert.AreEqual(userEntity.Id, result.Id);
        }

        [TestMethod]
        public void When_FirstOrDefault_Expect_False()
        {
            var result = repository.FirstOrDefault(u => u.Id == userEntity.Id);

            Assert.IsNull(result);
        }
    }
}
