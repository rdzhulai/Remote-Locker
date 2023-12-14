export interface StateType {
    user: UserType | null;
}

export interface UserType {
    id: number;
    name: string;
    password: string;
    admin: boolean;
    locker_id: number;
}

export enum Actions {
    SignInAccount,
}

export interface SignInAccountAction {
    type: Actions.SignInAccount;
    payload: UserType;
}

export type ActionType = SignInAccountAction;