module nrzi_decoder (
    input logic clk,
    input logic n_rst,
    input logic d_p,
    input logic d_n,
    output logic d_out,
    output logic error
);
    logic next_out;
    assign next_out = !(d_p ^ d_out);

    always_ff @(posedge clk, negedge n_rst) begin
        if (!n_rst) begin
            d_out <= 1'b0;
        end else begin 
            d_out = next_out;
        end
    end

    assign error = !(d_p ^ d_n);
    
endmodule;