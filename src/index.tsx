import React from 'react';
import ReactDOM from 'react-dom';
import { make as App } from './App.gen';

ReactDOM.render(
    <App />,
    document.getElementById("root") as HTMLElement
  );