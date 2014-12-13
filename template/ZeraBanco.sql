DELETE FROM "main"."processos";
DELETE FROM "main"."relation";
DELETE FROM "main"."pessoas";
DELETE FROM "main"."audiencia";
UPDATE "main"."sqlite_sequence" SET "seq" = 0;
UPDATE "main"."sqlite_sequence" SET "seq" = (select max("advogados"."id") from "advogados") WHERE  "rowid" = 6;
UPDATE "main"."sqlite_sequence" SET "seq" = (select max("tipo_parte"."id") from "tipo_parte") WHERE  "rowid" = 5;


INSERT INTO 'main'.'pessoas' ('nome','nacional','advogado') VALUES ('Irmãos Gonçalves Comércio e Indústria Ltda','brasileira',0);
INSERT INTO 'main'.'pessoas' ('nome','nacional','advogado') VALUES ('Libio Gomes Medeiros','brasileira',0);
INSERT INTO 'main'.'pessoas' ('nome','nacional','advogado') VALUES ('FÁBIO ARRUDA e outro.','brasileira',0);
INSERT INTO 'main'.'pessoas' ('nome','nacional','advogado') VALUES ('Cimopar Móveis Ltda - ST Liberatti','brasileira',0);

INSERT INTO 'main'.'pessoas' ('nome','nacional','advogado') VALUES ('Ineiza Pereira Alves','brasileira',0);
INSERT INTO 'main'.'pessoas' ('nome','nacional','advogado') VALUES ('Odete José Bento','brasileira',0);
INSERT INTO 'main'.'pessoas' ('nome','nacional','advogado') VALUES ('Odair Veloso','brasileira',0);
INSERT INTO 'main'.'pessoas' ('nome','nacional','advogado') VALUES ('Caroline Nishimura','brasileira',0);

INSERT INTO 'main'.'processos' ('num_proc','classe') VALUES ('1000995-98.2014.8.22.0007','Procedimento do Juizado Especial Cível');
INSERT INTO 'main'.'processos' ('num_proc','classe') VALUES ('1000702-31.2014.8.22.0007','Procedimento do Juizado Especial Cível');
INSERT INTO 'main'.'processos' ('num_proc','classe') VALUES ('1002437-36.2013.8.22.0007','Procedimento do Juizado Especial Cível');
INSERT INTO 'main'.'processos' ('num_proc','classe') VALUES ('1002163-72.2013.8.22.0007','Procedimento do Juizado Especial Cível');

INSERT INTO 'main'.'audiencia' ('hora_audi','id_proc','data_audi','tipo_audi') VALUES ('08:00',(select id from processos where num_proc='1000995-98.2014.8.22.0007'),'22/10/2014',1);
INSERT INTO 'main'.'audiencia' ('hora_audi','id_proc','data_audi','tipo_audi') VALUES ('09:00',(select id from processos where num_proc='1000702-31.2014.8.22.0007'),'22/10/2014',1);
INSERT INTO 'main'.'audiencia' ('hora_audi','id_proc','data_audi','tipo_audi') VALUES ('09:30',(select id from processos where num_proc='1002437-36.2013.8.22.0007'),'22/10/2014',1);
INSERT INTO 'main'.'audiencia' ('hora_audi','id_proc','data_audi','tipo_audi') VALUES ('10:30',(select id from processos where num_proc='1002163-72.2013.8.22.0007'),'22/10/2014',1);

INSERT INTO 'main'.'relation' ('id_proc','id_pessoa','tipo_parte','status') VALUES ((select id from processos where num_proc='1000995-98.2014.8.22.0007'),(select id from pessoas where nome='Irmãos Gonçalves Comércio e Indústria Ltda'),147,0);
INSERT INTO 'main'.'relation' ('id_proc','id_pessoa','tipo_parte','status') VALUES ((select id from processos where num_proc='1000702-31.2014.8.22.0007'),(select id from pessoas where nome='Libio Gomes Medeiros'),147,0);
INSERT INTO 'main'.'relation' ('id_proc','id_pessoa','tipo_parte','status') VALUES ((select id from processos where num_proc='1002437-36.2013.8.22.0007'),(select id from pessoas where nome='FÁBIO ARRUDA e outro.'),147,0);
INSERT INTO 'main'.'relation' ('id_proc','id_pessoa','tipo_parte','status') VALUES ((select id from processos where num_proc='1002163-72.2013.8.22.0007'),(select id from pessoas where nome='Cimopar Móveis Ltda - ST Liberatti'),147,0);

INSERT INTO 'main'.'relation' ('id_proc','id_pessoa','tipo_parte','status') VALUES ((select id from processos where num_proc='1000995-98.2014.8.22.0007'),(select id from pessoas where nome='Ineiza Pereira Alves'),11,0);
INSERT INTO 'main'.'relation' ('id_proc','id_pessoa','tipo_parte','status') VALUES ((select id from processos where num_proc='1000702-31.2014.8.22.0007'),(select id from pessoas where nome='Odete José Bento'),11,0);
INSERT INTO 'main'.'relation' ('id_proc','id_pessoa','tipo_parte','status') VALUES ((select id from processos where num_proc='1002437-36.2013.8.22.0007'),(select id from pessoas where nome='Odair Veloso'),11,0);
INSERT INTO 'main'.'relation' ('id_proc','id_pessoa','tipo_parte','status') VALUES ((select id from processos where num_proc='1002163-72.2013.8.22.0007'),(select id from pessoas where nome='Caroline Nishimura'),11,0);
