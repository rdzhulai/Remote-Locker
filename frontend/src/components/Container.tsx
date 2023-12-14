import { ReactNode } from "react"
interface Props {
    children: ReactNode
}
const Container = ({ children }: Props) => {
    return (
        <main className="mt-5">{children}</main>
    )
}

export default Container