import { useReducer } from "react";
import SignInPage from "./pages/SignInPage";
import Container from "./components/Container";
import { BrowserRouter, Route, Routes } from "react-router-dom";
import StateContext from "./state/StateContext";
import ControlPage from "./pages/ControlPage";
import AccountSettingsPage from "./pages/AccountSettingsPage";
import initialState from "./state/initialState";
import reducer from "./state/reducer";

function App() {
  const [state, dispatch] = useReducer(reducer, initialState);
  return (
    <BrowserRouter>
      <StateContext.Provider value={{ state, dispatch }}>
        <Container>
          <Routes>
            <Route path="/" element={<SignInPage />} />
            <Route path="/control" element={<ControlPage />} />
            <Route path="/settings" element={<AccountSettingsPage />} />
          </Routes>
        </Container>
      </StateContext.Provider>
    </BrowserRouter>
  );
}

export default App;
