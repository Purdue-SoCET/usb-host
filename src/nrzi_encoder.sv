module nrzi_encoder (
    input logic clk,
    input logic n_rst,
    input logic data_in,
    output logic d_p,
    output logic d_n
);
    logic next_data, out;

    assign next_data = !(data_in ^ out);

    always_ff @(posedge clk, negedge n_rst) begin
        if (!n_rst) begin
            out <= 1'b1;
        end else begin 
            out <= next_data;
        end
    end

    assign d_p = out;
    assign d_n = !out;

endmodule;