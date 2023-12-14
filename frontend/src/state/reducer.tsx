import { StateType, ActionType, Actions } from "../types/state";

const reducer = (state: StateType, { type, payload }: ActionType) => {
    switch (type) {
        case Actions.SignInAccount:
            return { ...state, user: payload };
        default:
            return state;
    }
};

export default reducer;