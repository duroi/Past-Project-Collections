import React from 'react';
import { BrowserRouter, Switch, Route } from 'react-router-dom';
import Tools from '../components/dashboard/Tools';
const AppRouter = () => (
  <BrowserRouter>
    <div className="container">
      <Header />
      <div className="main-content">
        <Switch>
          <Route component={Tools} path="/" exact={true} />
        </Switch>
      </div>
    </div>
  </BrowserRouter>
);
export default AppRouter;