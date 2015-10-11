/*
 * Copyright 2015 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#ifndef MYQTIMER_H
#define MYQTIMER_H

#include <qt4/QtCore/qthread.h>
#include <qt4/QtCore/QObject>
#include <qt4/QtCore/qmutex.h>
#include <signal.h>
class MyQTimer : public QThread
{
    struct entero_EMutua{
      int interv;
      QMutex c_;
      void set(int interv_){
	c_.lock();
	interv=interv_;
	c_.unlock();
      }
      int get(){
	c_.lock();
	int aux= interv;
	c_.unlock();
	return aux;
      }
    };
      
    Q_OBJECT
    entero_EMutua mseg;
public:
  MyQTimer();
public slots:
  void setseg(int seg);
protected:
  virtual void run();
signals:
  void senal();
};

#endif // MYQTIMER_H
