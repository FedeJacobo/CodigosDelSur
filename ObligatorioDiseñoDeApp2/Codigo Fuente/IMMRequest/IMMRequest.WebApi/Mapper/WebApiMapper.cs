using AutoMapper;
using IMMRequest.Entities;
using IMMRequest.IDataImporter;
using IMMRequest.WebApi.Models;

namespace IMMRequest.WebApi.Mapper
{
    public class WebApiMapper : IWebApiMapper
    {
        public IMapper Configure()
        {
            var config = new MapperConfiguration(cfg =>
            {
                cfg.CreateMap<UserModelIn, UserEntity>();
                cfg.CreateMap<UserEntity, UserModelOut>();

                cfg.CreateMap<RequestModelIn, RequestEntity>().ForMember(r => r.Status,
                        opt => opt.MapFrom(rM => rM.Status.ToUpper().Trim() == "CREADA" ? RequestStatus.CREADA :
                                                 rM.Status.ToUpper().Trim() == "ACEPTADA" ? RequestStatus.ACEPTADA :
                                                 rM.Status.ToUpper().Trim() == "DENEGADA" ? RequestStatus.DENEGADA :
                                                 rM.Status.ToUpper().Trim() == "ENREVISION" ? RequestStatus.ENREVISION :
                                                 rM.Status.ToUpper().Trim() == "EN REVISION" ? RequestStatus.ENREVISION :
                                                 rM.Status.ToUpper().Trim() == "FINALIZADA" ? RequestStatus.FINALIZADA :
                                                 RequestStatus.ERROR));
                cfg.CreateMap<RequestEntity, RequestModelOut>().ForMember(rE => rE.Status,
                        opt => opt.MapFrom(r => r.Status.ToString()));

                cfg.CreateMap<TypeReqModelIn, TypeReqEntity>();
                cfg.CreateMap<TypeReqEntity, TypeReqModelOut>();

                cfg.CreateMap<AdditionalFieldModelIn, AdditionalFieldEntity>().ForMember(a => a.Type,
                        opt => opt.MapFrom(aE => aE.Type.ToUpper().Trim() == "TEXTO"? AdditionalFieldType.TEXTO : 
                                                 aE.Type.ToUpper().Trim() == "ENTERO" ? AdditionalFieldType.ENTERO : 
                                                 aE.Type.ToUpper().Trim() == "FECHA" ? AdditionalFieldType.FECHA :
                                                 aE.Type.ToUpper().Trim() == "BOOL" ? AdditionalFieldType.BOOL :
                                                 AdditionalFieldType.ERROR));
                cfg.CreateMap<AdditionalFieldEntity, AdditionalFieldModelOut>()/*.ForMember(a => a.Type,
                        opt => opt.MapFrom(aE => aE.Type.ToString()))*/;

                cfg.CreateMap<AreaModelIn, AreaEntity>();
                cfg.CreateMap<AreaEntity, AreaModelOut>();

                cfg.CreateMap<TopicModelIn, TopicEntity>();
                cfg.CreateMap<TopicEntity, TopicModelOut>();

                cfg.CreateMap<ParameterModelIn, Parameter>();
            });

            return config.CreateMapper();
        }
    }
}
