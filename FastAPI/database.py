from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

db_url = "postgresql://rj1aditya:8085@localhost/my_app_db"
engine = create_engine(db_url)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)
